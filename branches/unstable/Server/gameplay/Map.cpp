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
Map::Map(QString filename) : mapSize(0), tileSize(1)
{
    QDomDocument doc;
    int x, y;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        cerr << "Cannot open file" << endl;
        return;
    }

    if (!doc.setContent(&file))
    {
        cerr << "Unusable file" << endl;
        file.close();
        return;
    }

    file.close();
    QDomElement map_e = doc.documentElement();

    if (map_e.tagName() != "map")
    {
        cerr << "Not a map element" << endl;
        return;
    }

    mapSize  = map_e.attribute("width", "0").toInt(); //Stick to square maps for now
    //height = map_e.attribute("height", "0").toInt();
    tileSize = map_e.attribute("tileSize", "1").toInt();

    // create tiles array
    tiles = new Tile*[mapSize];
    for(int i=0; i < mapSize; i++)
        *(tiles + i) = new Tile[mapSize];


    /*tiles = (Tile***) malloc(sizeof(Tile**) * mapSize); //This is fucking insane

    for (int x = 0; x < mapSize; ++x)
    {
        tiles[x] = (Tile**) malloc(sizeof(Tile*) * mapSize);
        for (int y = 0; y < mapSize; ++y)
        {
            tiles[x][y] = NULL;
        }
    }*/

    /*QDomNodeList tile_l = map_e.elementsByTagName("tile");
    for (int ti = 0; ti < tile_l.count(); ++ti)
    {
        QDomElement tile_e = tile_l.item(ti).toElement();
        QDomNodeList physics_l = tile_e.elementsByTagName("physics");
        for (int pi = 0; pi < physics_l.count(); ++pi)
        {
            QDomElement physics_e = physics_l.item(pi).toElement();
            x = tile_e.attribute("x", "0").toInt();
            y = tile_e.attribute("y", "0").toInt();

            if (tile(x, y) == NULL)
                tiles[x][y] = new Tile(x, y, true);
        }
    }*/
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
Tile Map::tile(int x, int y)
{
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
void Map::move(Ship *ship, QPoint old_position, QPoint new_position, int size)
{
    int xl1 = Pix2Tile(old_position.x());
    int xr1 = Pix2Tile(old_position.x() + size);
    int xl2 = Pix2Tile(new_position.x());
    int xr2 = Pix2Tile(new_position.x() + size);
    int yb1 = Pix2Tile(old_position.y());
    int yt1 = Pix2Tile(old_position.y() + size);
    int yb2 = Pix2Tile(new_position.y());
    int yt2 = Pix2Tile(new_position.y() + size);
    for (int x = MIN(xl1, xl2); x <= MAX(xr1, xr2); ++x)
    {
        for (int y = MIN(yb1, yb2); y <= MAX(yt1, yt2); ++y)
        {
            if (x < xl1 || x > xr1 || y < yb1 || y > yt1) // if not in old_position
            {
                if (x <= xl2 && x >= xr2 && y >= yb1 && y <= yt1) // if in new position
                {
                    ensure(x, y);
                    tile(x, y).add(ship);
                }
            }
            else // is in old position!
            {
                if (x < xl2 || x > xr2 || y < yb2 || y > yt2) // if not in new position
                {
                    tile(x, y).remove(ship);
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
    int old_x = Pix2Tile(old_position.x());
    int old_y = Pix2Tile(old_position.y());
    int new_x = Pix2Tile(new_position.x());
    int new_y = Pix2Tile(new_position.y());
    ensure(new_x, new_y);
    tile(new_x, new_y).add(shot);
    tile(old_x, old_y).remove(shot);
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
void Map::add(Ship *ship, QPoint location, int size)
{
    int x1 = Pix2Tile(location.x());
    int x2 = Pix2Tile(location.x() + size);
    int y1 = Pix2Tile(location.y());
    int y2 = Pix2Tile(location.y() + size);
    for (int x = x1; x < x2; ++x)
    {
        for (int y = y1; y <= y2; ++y)
        {
            ensure(x, y);
            tile(x, y).add(ship);
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
void Map::add(Shot *shot, QPoint location)
{
    int x = Pix2Tile(location.x());
    int y = Pix2Tile(location.y());
    ensure(x, y);
    tile(x, y).add(shot);
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
void Map::remove(Ship *ship, QPoint location, int size)
{
    int x1 = Pix2Tile(location.x());
    int x2 = Pix2Tile(location.x() + size);
    int y1 = Pix2Tile(location.y());
    int y2 = Pix2Tile(location.y() + size);
    for (int x = x1; x < x2; ++x)
    {
        for (int y = y1; y <= y2; ++y)
        {
            tile(x, y).remove(ship);
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
    int x = Pix2Tile(location.x());
    int y = Pix2Tile(location.y());
    tile(x, y).remove(shot);
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
    Tile atile = tile(x, y);

    return atile.isWall();
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
int Map::canMove(QPoint position, bool vertical, int size, int distance)
{
    int xpos  = Pix2Tile(position.x()), ypos = Pix2Tile(position.y());
    int start = vertical ? ypos : xpos;   //Denotes object beginning tile
    int end   = start + Pix2Tile(distance);                         //Denotes destination tile

    if (vertical)
        cout << "Moving from: " << start << "y to " << end << "y" << endl;
    else
        cout << "Moving from: " << start << "x to " << end << "x" << endl;

    if (distance > 0) //moving in +ve direction
    {
        for (int i = start; i <= end; ++i) //Check tiles along the way in +ve dir
        {
            if (isWall(i, vertical ? xpos : ypos) || start + i > mapSize) //if we hit a wall or go out of bounds
                    return Tile2Pix(i - 1 - start); //distance = one before current - starting tile
        }
    }
    else //moving in -ve direction
    {
        for (int i = start; i >= end; --i) //Check tiles along the way in -ve dir
        {
            if (isWall(i, vertical ? xpos : ypos) || start - i < 0) //if we hit a wall or go out of bounds
                return Tile2Pix(start - i + 1); //distance = starting tile - one before current
        }
    }

    return distance; //No obstacles encountered
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
    /*if (tile(x, y) == NULL) {
        tiles[x][y] = new Tile(x, y);
    }*/
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
    /*Tile atile = tile(x, y);
    if (!atile.empty())
    {
        // tile not emtpy, DO NOT CLEAN!
        return;
    }
    delete tiles[x][y];
    tiles[x][y] = NULL;*/
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::drawMap
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

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::ships
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  std::list<Ship*> Map::ships(QPoint center, int width=1024, int height=768)
--              center : center of the viewport
--              width : width of the viewport
--              height : height of the viewport
--
--  NOTES:      Returns all ships in a given viewport.
--              The viewport will have a margin of 50% of every side (quadrupaling total viewport area)
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
std::list<Ship*> Map::ships(QPoint center, int width, int height) {
    std::list<Ship*> list, list2;
    int left   = MAX(0       , Pix2Tile(center.x() - width));
    int right  = MIN(width-1 , Pix2Tile(center.x() + width));
    int bottom = MAX(0       , Pix2Tile(center.y() - width));
    int top    = MIN(height-1, Pix2Tile(center.x() + width));
    for (int x=left; x <= right; ++x) {
        for (int y=bottom; y <= top; ++x) {
            list2 = tile(x, y).getShips();
            list.sort();
            list2.sort();
            list.merge(list2);
        }
    }
    list.unique();
    return list;
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::shots
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  std::list<Shot*> Map::shots(QPoint center, int width=1024, int height=768)
--              center : center of the viewport
--              width : width of the viewport
--              height : height of the viewport
--
--  NOTES:      Returns all shots in a given viewport.
--              The viewport will have a margin of 50% of every side (quadrupaling total viewport area)
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
std::list<Shot*> Map::shots(QPoint center, int width, int height) {
    std::list<Shot*> list, list2;
    int left   = MAX(0       , Pix2Tile(center.x() - width));
    int right  = MIN(width-1 , Pix2Tile(center.x() + width));
    int bottom = MAX(0       , Pix2Tile(center.y() - width));
    int top    = MIN(height-1, Pix2Tile(center.x() + width));
    for (int x=left; x <= right; ++x) {
        for (int y=bottom; y <= top; ++x) {
            list2 = tile(x, y).getShots();
            list.sort();
            list2.sort();
            list.merge(list2);
        }
    }
    list.unique();
    return list;
}
