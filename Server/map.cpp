#include "map.h"
#include "general.h"
#include <QPoint>
#include <QString>
#include <QDomDocument>
#include <QFile>
#include <iostream>

using namespace std;

Map::Map(QString filename) {
    QDomDocument doc;
    int x, y;
    bool wall;
    Tile *tile;
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
            cout << "Found Tile(" << x << ", " << y << ", " << (wall ? "true" : "false") << ");" << endl;
            add(new Tile(x, y, wall), x, y);
            property_n = property_n.nextSibling();
        }
        tile_n = tile_n.nextSibling();
    }
}

void Map::add(Tile *tile, int x, int y) {
    tiles[x][y] = tile;
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
Tile *Map::tile(QPoint position) {
    return this->tiles[position.x() / this->tileSize][position.y() / this->tileSize];
}

Tile *Map::tile(int x, int y) {
    return this->tiles[x][y];
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
    int xl1 = old_position.x() / tileSize;
    int xr1 = (old_position.x() + size) / tileSize;
    int xl2 = new_position.x() / tileSize;
    int xr2 = (new_position.x() + size) / tileSize;
    int yb1 = old_position.y() / tileSize;
    int yt1 = (old_position.y() + size) / tileSize;
    int yb2 = new_position.y() / tileSize;
    int yt2 = (new_position.y() + size) / tileSize;
    for (int x=MIN(xl1, xl2); x <= MAX(xr1, xr2); ++x) {
        for (int y=MIN(yb1, yb2); y <= MAX(yt1, yt2); ++y) {
            if (x < xl1 || x > xr1 || y < yb1 || y > yt1) { // if not in old_position
                if (x <= xl2 && x >= xr2 && y >= yb1 && y <= yt1) { // if in new position
                    tile(x, y)->add(ship);
                }
            } else {    // is in old position!
                if (x < xl2 || x > xr2 || y < yb2 || y > yt2) { // if not in new position
                    tile(x, y)->remove(ship);
                }
            }
        }
    }

}

void Map::move(Shot *shot, QPoint old_position, QPoint new_position) {
    tile(old_position)->remove(shot);
    tile(new_position)->add(shot);
}

void Map::add(Ship *ship, QPoint location, int size) {
    int x1 = location.x() / tileSize;
    int x2 = (location.x() + size) / tileSize;
    int y1 = location.y() / tileSize;
    int y2 = (location.y() + size) / tileSize;
    for (int x=x1; x < x2; ++x) {
        for (int y=y1; y<=y2; ++y) {
            tile(x, y)->add(ship);
        }
    }
}

void Map::add(Shot *shot, QPoint location) {
    tile(location)->add(shot);
}

void Map::remove(Ship *ship, QPoint location, int size) {
    int x1 = location.x() / tileSize;
    int x2 = (location.x() + size) / tileSize;
    int y1 = location.y() / tileSize;
    int y2 = (location.y() + size) / tileSize;
    for (int x=x1; x < x2; ++x) {
        for (int y=y1; y<=y2; ++y) {
            tile(x, y)->remove(ship);
        }
    }
}

void Map::remove(Shot *shot, QPoint location) {
    tile(location)->remove(shot);
}

bool Map::isWall(QPoint location) {
    return tile(location)->isWall();
}

bool Map::isWall(int x, int y) {
    return tile(x, y)->isWall();
}

int Map::canMove(QPoint position, bool vertical, int size, int distance) {
    // movement
    int begin = MAX(0, MIN((vertical ? height : width), (vertical ? position.y() : position.x()) / tileSize));
    int stop = MAX(0, MIN((vertical ? height : width), ((vertical ? position.y() : position.x()) + distance) / tileSize));
    // line segment
    int start = MAX(0, MIN((vertical ? width : height), (vertical ? position.x() : position.y()) / tileSize));
    int end = MAX(0, MIN((vertical ? width : height), ((vertical ? position.x() : position.y()) + size) / tileSize));
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
