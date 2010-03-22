#include "Map.h"
#include "general.h"
#include <QPoint>
#include <QString>
#include <QDomDocument>
#include <QFile>
#include <iostream>
#include "stdlib.h"

using namespace std;

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::Map
--
--  DATE:       February 17, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Map(QString filename)
--              filename : filename of the map xml file
--
--  NOTES:      Constructor that parses an XML file.
--
--  RETURNS:    Map object (constructor).
--
------------------------------------------------------------------------------*/
Map::Map(QString filename):width(0), height(0), tileSize(1) {
    QDomDocument doc;
    int x, y;
    bool wall;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        cerr << "Cannot open file" << endl;
        return;
    }
    if (!doc.setContent(&file)) {
        cerr << "Unusable file" << endl;
        file.close();
        return;
    }
    file.close();
    QDomElement map_e = doc.documentElement();
    if (map_e.tagName() != "map") {
        cerr << "Not a map element" << endl;
        return;
    }
    width = map_e.attribute("width", "0").toInt();
    height = map_e.attribute("height", "0").toInt();
    tileSize = map_e.attribute("tileSize", "1").toInt();

    // create tiles array
    tiles = (Tile***)malloc(sizeof(Tile**) * width);
    for (int x=0; x < width; ++x) {
        tiles[x] = (Tile**)malloc(sizeof(Tile*) * height);
        for (int y=0; y < height; ++y) {
            tiles[x][y] = NULL;
        }
    }
    QDomNode tile_n = map_e.firstChild();
    while (!tile_n.isNull()) {
        QDomElement tile_e = tile_n.toElement();
        if (tile_e.isNull()) {
            continue;
        }
        if (tile_e.tagName() != "tile") {
            continue;
        }
        QDomNode property_n = tile_e.firstChild();
        while (!property_n.isNull()) {
            QDomElement property_e = property_n.toElement();
            if (property_e.isNull()) {
                property_n = property_n.nextSibling();
                continue;
            }
            if (property_e.tagName() != "physics") {
                property_n = property_n.nextSibling();
                continue;
            }
            x = tile_e.attribute("x", "0").toInt();
            y = tile_e.attribute("y", "0").toInt();
            wall = (property_e.attribute("hit", "") != "space");
            if (tile(x, y) == NULL) {
                tiles[x][y] = new Tile(x, y, wall);
            }
            property_n = property_n.nextSibling();
        }
        tile_n = tile_n.nextSibling();
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::tile
--
--  DATE:       February 17, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile tile(int x, int y)
--              x : x position along grid of target tile
--              y : y position along grid of target tile
--
--  NOTES:      Returns the tile at the specified position.
--
--  RETURNS:    Tile at the specified position.
--
------------------------------------------------------------------------------*/
Tile *Map::tile(int x, int y) {
    return tiles[x][y];
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::move
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Ship *ship, QPoint old_position, QPoint new_position, int size)
--              Ship *ship : Pointer to the ship to move
--              QPoint old_position : the previous position of the ship.
--              QPoint new_position : the new position of the ship.
--              int size : The size of a ship
--
--  NOTES:      Moves the ship from its old tile to the new one.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::move(Ship *ship, QPoint old_position, QPoint new_position, int size) {
    int xl1 = C2G(old_position.x());
    int xr1 = C2G(old_position.x() + size);
    int xl2 = C2G(new_position.x());
    int xr2 = C2G(new_position.x() + size);
    int yb1 = C2G(old_position.y());
    int yt1 = C2G(old_position.y() + size);
    int yb2 = C2G(new_position.y());
    int yt2 = C2G(new_position.y() + size);
    for (int x=MIN(xl1, xl2); x <= MAX(xr1, xr2); ++x) {
        for (int y=MIN(yb1, yb2); y <= MAX(yt1, yt2); ++y) {
            if (x < xl1 || x > xr1 || y < yb1 || y > yt1) { // if not in old_position
                if (x <= xl2 && x >= xr2 && y >= yb1 && y <= yt1) { // if in new position
                    ensure(x, y);
                    tile(x, y)->add(ship);
                }
            } else {    // is in old position!
                if (x < xl2 || x > xr2 || y < yb2 || y > yt2) { // if not in new position
                    tile(x, y)->remove(ship);
                    clean(x, y);
                }
            }
        }
    }

}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::move
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Shot *shto, QPoint old_position, QPoint new_position)
--              Shot *shot : Pointer to the shot to move
--              QPoint old_position : the previous position of the shot.
--              QPoint new_position : the new position of the shot.
--
--  NOTES:      Moves the shot from its old tile to the new one.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::move(Shot *shot, QPoint old_position, QPoint new_position) {
    int old_x = C2G(old_position.x());
    int old_y = C2G(old_position.y());
    int new_x = C2G(new_position.x());
    int new_y = C2G(new_position.y());
    ensure(new_x, new_y);
    tile(new_x, new_y)->add(shot);
    tile(old_x, old_y)->remove(shot);
    clean(old_x, old_y);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::add
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Ship *ship, QPoint location, int size)
--              Ship *ship : Pointer to the ship to add
--              QPoint location : location of the ship (so it can be added to the map).
--              size : Size of a ship.
--
--  NOTES:      Adds a new ship to the map.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::add(Ship *ship, QPoint location, int size) {
    int x1 = C2G(location.x());
    int x2 = C2G(location.x() + size);
    int y1 = C2G(location.y());
    int y2 = C2G(location.y() + size);
    for (int x=x1; x < x2; ++x) {
        for (int y=y1; y<=y2; ++y) {
            ensure(x, y);
            tile(x, y)->add(ship);
        }
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::add
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Shot *shot, QPoint location, int size)
--              Shot *shot : Pointer to the shot to add
--              QPoint location : location of the shot (so it can be added to the map).
--
--  NOTES:      Adds a new shot to the map.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::add(Shot *shot, QPoint location) {
    int x = C2G(location.x());
    int y = C2G(location.y());
    ensure(x, y);
    tile(x, y)->add(shot);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::remove
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Ship *ship, QPoint location, int size)
--              Ship *ship : Pointer to the ship to remove
--              QPoint location : location of the ship.
--              size : Size of a ship.
--
--  NOTES:      Removes a ship from the map.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::remove(Ship *ship, QPoint location, int size) {
    int x1 = C2G(location.x());
    int x2 = C2G(location.x() + size);
    int y1 = C2G(location.y());
    int y2 = C2G(location.y() + size);
    for (int x=x1; x < x2; ++x) {
        for (int y=y1; y<=y2; ++y) {
            tile(x, y)->remove(ship);
            clean(x, y);
        }
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::remove
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Shot *shot, QPoint location, int size)
--              Shot *shot : Pointer to the shot to remove
--              QPoint location : location of the shot.
--              size : Size of a shot.
--
--  NOTES:      Removes a shot from the map.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::remove(Shot *shot, QPoint location) {
    int x = C2G(location.x());
    int y = C2G(location.y());
    tile(x, y)->remove(shot);
    clean(x, y);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::isWall
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  bool isWall(int x, int y)
--              x : x position in grid
--              y : y position in grid
--
--  NOTES:      checks if a tile is a wall.
--
--  RETURNS:    true if the tile is a wall, else false.
--
------------------------------------------------------------------------------*/
bool Map::isWall(int x, int y) {
    Tile *atile = tile(x, y);
    if (atile == NULL) {
        return false;
    }
    return atile->isWall();
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::canMove
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  int canMove(QPoint position, bool vertical, int size, int distance)
--              position : position of object we'd like to move (top-left corner)
--              vertical : true if trying to move vertically, false if moving horizontally
--              size : size of the object we are moving
--              distance : the distance we would like to try and move
--
--  NOTES:      calculates how far an object can move in any given direction (up to max of distance)
--
--  RETURNS:    The number of grid units the object can move or -1 if an error occured.
--
------------------------------------------------------------------------------*/
int Map::canMove(QPoint position, bool vertical, int size, int distance) {
    // line segment
    int start = C2G(vertical ? position.x() : position.y());
    int end = C2G((vertical ? position.x() : position.y()) + size);
    // movement
    int begin = C2G((vertical ? position.y() : position.x()) + (distance > 0 ? size : 0));
    int stop = C2G((vertical ? position.y() : position.x()) + (distance > 0 ? size : 0) + distance);
    // sanity checks:
    if (start < 0 || end < 0 || begin < 0) {
        cerr << "value " << start << 'x' << end << ',' << begin << 'x' << stop << " below 0" << endl;
        return -1;
    }
    if (vertical && (start > width || end > width || begin > height)) {
        cerr << "vertical value " << start << 'x' << end << ',' << begin << 'x' << stop << " above " << width << 'x' << height << endl;
        return -1;
    }
    if (!vertical && (start > height || end > height || begin > width)) {
        cerr << "horizontal " << start << 'x' << end << ',' << begin << 'x' << stop << " value above " << width << 'x' << height << endl;
        return -1;
    }
    cout << "values: " << start << 'x' << end << ',' << begin << 'x' << stop << endl;
    // calculation
    if (distance > 0) {
        for (int i=begin; i <= stop; ++i) {
            for (int j=start; j <= end; ++j) {
                if ((!vertical && isWall(i, j)) || (vertical && isWall(j, i))) {
                    return MAX(i - start - 1, -(i - start - 1));
                }
            }
        }
    } else {
        for (int i=begin; i >= stop; --i) {
            for (int j=start; j >= end; --j) {
                if ((!vertical && isWall(i, j)) || (vertical && isWall(j, i))) {
                    return MAX(i - start -1, -(i - start -1));
                }
            }
        }
    }
    return MAX(stop - start - 1, -(stop - start - 1));
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::ensure
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  void ensure(int x, int y)
--              x : x position on grid
--              y : y position on grid
--
--  NOTES:      ensures that there is a tile object at x,y (if tile already exists, nothing happens)
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Map::ensure(int x, int y) {
    if (tile(x, y) == NULL) {
        tiles[x][y] = new Tile(x, y);
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::clean
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  void clean(int x, int y)
--              x : x position on grid
--              y : y position on grid
--
--  NOTES:      Cleans the specified coordinates. If the tile is empty (and not a wall), it is deleted.
--              This is used to minimize ram usage (which would otherwise escalate badly for larger maps)
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Map::clean(int x, int y) {
    Tile *atile = tile(x, y);
    if (atile == NULL) {
        // tile doesn't exist, nothing to clean
        return;
    }
    if (!atile->empty()) {
        // tile not emtpy, DO NOT CLEAN!
        return;
    }
    delete tile(x, y);
    tiles[x][y] = NULL;
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::Tile
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile(int new_x, int new_y)
--              new_x : tile x grid location
--              new_y : tile x grid location
--
--  NOTES:      Creates a new non-wall tile at position x,y.
--              Note: This does NOT add it to the map!
--                    The map is the only class that should be adding tiles.
--
--  RETURNS:    Tile object (constructor).
--
------------------------------------------------------------------------------*/
Tile::Tile(int new_x, int new_y):wall(false), x(new_x), y(new_y) {}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::Tile
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile(int new_x, int new_y, bool new_wall)
--              new_x : tile x grid location
--              new_y : tile x grid location
--              new_wall : true if tile should be a wall, else false
--
--  NOTES:      Creates a new tile at position x,y with posibility of being a wall.
--              Note: This does NOT add it to the map!
--                    The map is the only class that should be adding tiles.
--
--  RETURNS:    Tile object (constructor).
--
------------------------------------------------------------------------------*/
Tile::Tile(int new_x, int new_y, bool new_wall): wall(new_wall), x(new_x), y(new_y) {}


/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::isWall
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile()
--
--  NOTES:      Returns true if the tile is a wall, else false.
--
--  RETURNS:    true if the tile is a wall, else false.
--
------------------------------------------------------------------------------*/
bool Tile::isWall() {
    return wall;
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::add
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile(Ship *ship)
--              Ship *ship : ship to add to the tile
--
--  NOTES:      Adds a ship to the tile.
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Tile::add(Ship *ship) {
    ships.push_back(ship);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::add
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile(Shot *shot)
--              Shot *shot : ship to add to the tile
--
--  NOTES:      Adds a shot to the tile.
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Tile::add(Shot *shot) {
    shots.push_back(shot);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::remove
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile(Ship *ship)
--              Ship *ship : ship to remove from the tile
--
--  NOTES:      Removes a ship from the tile.
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Tile::remove(Ship *ship) {
    ships.remove(ship);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::remove
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile(Shot *shot)
--              Shot *shot : shot to remove from the tile
--
--  NOTES:      Removes a shot from the tile.
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Tile::remove(Shot *shot) {
    shots.remove(shot);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::numShips
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  numShips()
--
--  NOTES:      Counts the number of ships in the tile.
--
--  RETURNS:    The number of ships in the tile.
--
------------------------------------------------------------------------------*/
int Tile::numShips() {
    return ships.size();
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::numShots
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  numShots()
--
--  NOTES:      Counts the number of shots in the tile.
--
--  RETURNS:    The number of shots in the tile.
--
------------------------------------------------------------------------------*/
int Tile::numShots() {
    return shots.size();
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::empty
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  int empty()
--
--  NOTES:      Checks if the tile is empty (and not a wall).
--
--  RETURNS:    true if the tile is empty and not a wall, else false.
--
------------------------------------------------------------------------------*/
bool Tile::empty() {
    return (!isWall() && numShots() == 0 && numShips() == 0);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::drawMap
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  void drawMap()
--
--  NOTES:      Draws the map to stdout (used for testing & debuging maps).
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Map::drawMap(){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            std::cout << (isWall(i, j)?"X":".");
        }
        std::cout << std::endl;
    }
}

