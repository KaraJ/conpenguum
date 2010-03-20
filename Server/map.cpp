#include "map.h"
#include "general.h"
#include <QPoint>
#include <QString>
#include <QDomDocument>
#include <QFile>
#include <iostream>
#include "stdlib.h"

using namespace std;

Map::Map(QString filename):height(0), width(0), tileSize(1) {
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
    tileSize = map_e.attribute("tileWidth", "1").toInt();

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
--  FUNCTION:   tile
--
--  DATE:       February 17, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile tile(QPoint position)
--
--  NOTES:      Returns the tile at the specified position.
--
--  RETURNS:    Tile at the position.
--
------------------------------------------------------------------------------*/

Tile *Map::tile(int x, int y) {
    return tiles[x][y];
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   move
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Shot, QPoint)
--              Shot shot : The shot to move
--              QPoint old_position : the previous position of the ship.
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

void Map::add(Shot *shot, QPoint location) {
    int x = C2G(location.x());
    int y = C2G(location.y());
    ensure(x, y);
    tile(x, y)->add(shot);
}

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

void Map::remove(Shot *shot, QPoint location) {
    int x = C2G(location.x());
    int y = C2G(location.y());
    tile(x, y)->remove(shot);
    clean(x, y);
}

bool Map::isWall(int x, int y) {
    Tile *atile = tile(x, y);
    if (atile == NULL) {
        return false;
    }
    return atile->isWall();
}

int Map::canMove(QPoint position, bool vertical, int size, int distance) {
    // movement
    int begin = MAX(0, MIN((vertical ? height : width)-1, C2G(vertical ? position.y() : position.x())));
    int stop = MAX(0, MIN((vertical ? height : width)-1, C2G((vertical ? position.y() : position.x()) + distance)));
    // line segment
    int start = MAX(0, MIN((vertical ? width : height)-1, C2G(vertical ? position.x() : position.y())));
    int end = MAX(0, MIN((vertical ? width : height)-1, C2G((vertical ? position.x() : position.y()) + size)));
    if (distance > 0) {
        for (int i=begin; i <= stop; ++i) {
            for (int j=start; j <= end; ++j) {
                if ((!vertical && isWall(i, j)) || (vertical && isWall(j, i))) {
                    return i - start - 1;
                }
            }
        }
    } else {
        for (int i=begin; i >= stop; --i) {
            for (int j=start; j >= end; --j) {
                if ((!vertical && isWall(i, j)) || (vertical && isWall(j, i))) {
                    return i - start -1;
                }
            }
        }
    }
}

void Map::ensure(int x, int y) {
    if (tile(x, y) == NULL) {
        tiles[x][y] = new Tile(x, y);
    }
}

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
    tiles[x][y] == NULL;
}

Tile::Tile(int new_x, int new_y): x(new_x), y(new_y), wall(false) {}

Tile::Tile(int new_x, int new_y, bool new_wall): x(new_x), y(new_y), wall(new_wall) {}


bool Tile::isWall() {
    return wall;
}

void Tile::add(Ship *ship) {
    ships.push_back(ship);
}

void Tile::add(Shot *shot) {
    shots.push_back(shot);
}

void Tile::remove(Ship *ship) {
    ships.remove(ship);
}

void Tile::remove(Shot *shot) {
    shots.remove(shot);
}

int Tile::numShips() {
    return ships.size();
}

int Tile::numShots() {
    return shots.size();
}

bool Tile::empty() {
    return (!isWall() && numShots() == 0 && numShips() == 0);
}

// just for some quick testing
void Map::drawMap(){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            std::cout << (isWall(i, j)?"X":".");
        }
        std::cout << std::endl;
    }
}
