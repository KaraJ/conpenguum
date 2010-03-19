// EDITED VERSION OF WHAT DOUG PROVIDED. ONLY FOR USE IN TESTING THE BULLETS
// IN THE v0.2 BUILD. DO NOT PUT IN THE TRUNK EVER!

#ifndef _MAP_H
#define _MAP_H

#include <list>
#include <QPoint>
#include "newtObjects.h"
#include "shot.h"
#include "ship.h"

class Tile {
private:
    bool wall, fixed, x, y;
    std::list<int> ships;
    std::list<Shot> shots;
public:
    Tile(int x, int y);
    bool isWall(){return wall;}
    int numShips();
    int numShots;
    bool overlap(NewtObject object);
    void addShip(Ship ship);
    void addShot(Shot shot);
    void delShip(Ship ship);
    void delShot(Shot shot);
};

class Map {
private:
    Tile map[1024];
    int  width;    // map width in tiles
    int  height;   // map height in tiles
    int  tileSize; // length of tile edge in pixels
public:
    Map(int x, int y);
    void addShip(Ship ship);
    void removeShip(Ship ship);
    void addShot(Shot shot);
    void removeShot(Shot shot);
    void move(Ship ship);
    void move(Shot shot);
    int tileContents(QPoint pos);
    Tile tile(QPoint position);
};

#endif
