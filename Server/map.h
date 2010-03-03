// EDITED VERSION OF WHAT DOUG PROVIDED. ONLY FOR USE IN TESTING THE BULLETS
// IN THE v0.2 BUILD. DO NOT PUT IN THE TRUNK EVER!

#ifndef _MAP_H
#define _MAP_H

#include <list>
#include <QPoint>
#include "newtObjects.h"
#include "shot.h"
#include "ship.h"

#define MAX_MAP_HEIGHT 1024
#define MAX_MAP_WIDTH 102

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
    void add(Ship ship);
    void add(Shot shot);
    void remove(Ship ship);
    void remove(Shot shot);
};

class Map {
private:
    Tile tiles[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];
    int  width;    // map width in tiles
    int  height;   // map height in tiles
    int  tileSize; // length of tile edge in pixels
    Tile tile(QPoint position);
public:
    Map(int x, int y);
    void add(Ship ship);
    void add(Shot shot);
    void remove(Ship ship);
    void remove(Shot shot);
    void move(Ship ship, QPoint old_position);
    void move(Shot shot, QPoint old_position);
    int tileContents(QPoint pos);
};

#endif
