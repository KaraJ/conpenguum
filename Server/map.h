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
    std::list<Ship*> ships;
    std::list<Shot*> shots;
public:
    bool isWall();
    int numShips();
    int numShots();
    void add(Ship *ship);
    void add(Shot *shot);
    void remove(Ship *ship);
    void remove(Shot *shot);
    void setWall(){wall = true;}
};

class Map {
private :
    Tile tiles[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];
    int  width;    // map width in tiles
    int  height;   // map height in tiles
    int  tileSize; // length of tile edge in pixels
    Tile tile(QPoint position); // get by position
    Tile tile(int x, int y);    // get by grid coord
public:
    Map(QString filename);
    void add(Ship *ship, QPoint location, int size);
    void add(Shot *shot, QPoint location);
    void remove(Ship *ship, QPoint location, int size);
    void remove(Shot *shot, QPoint location);
    void move(Ship *ship, QPoint old_position, QPoint new_position, int size);
    void move(Shot *shot, QPoint old_position, QPoint new_position);
    bool isWall(QPoint);    // by location
    bool isWall(int x, int y);  // by grid
    int canMove(QPoint old_position, bool vertical, int size, int distance);
    Map(); // for testing, so damn ugly
    void drawMap(); // testing again, going to make me throw up
};

#endif
