#ifndef _MAP_H
#define _MAP_H

#include <list>
#include <QPoint>
#include "NewtObjects.h"
#include "Shot.h"
#include "Ship.h"

#define C2G(coord) ((coord) / tileSize)

class Tile {
private:
    bool wall;
    bool x;
    bool y;
    std::list<Ship*> ships;
    std::list<Shot*> shots;
public:
    Tile(int x, int y);
    Tile(int x, int y, bool wall);
    bool isWall();
    int numShips();
    int numShots();
    void add(Ship *ship);
    void add(Shot *shot);
    void remove(Ship *ship);
    void remove(Shot *shot);
    bool empty();
    //test only
    void setWall(){wall = true;}
};

class Map {
private :
    Tile ***tiles;
    int  width;    // map width in tiles
    int  height;   // map height in tiles
    int  tileSize; // length of tile edge in pixels
    Tile *tile(int x, int y);    // get by grid coord
    void ensure(int x, int y);  // ensure grid location has a tile
    void clean(int x, int y);   // remove free tile memory if empty (saves LOTS of ram!!!)
    bool isWall(int x, int y);  // checks if grid coords has a wall tile
public:
    Map(QString filename);
    void add(Ship *ship, QPoint location, int size);
    void add(Shot *shot, QPoint location);
    void remove(Ship *ship, QPoint location, int size);
    void remove(Shot *shot, QPoint location);
    void move(Ship *ship, QPoint old_position, QPoint new_position, int size);
    void move(Shot *shot, QPoint old_position, QPoint new_position);
    int canMove(QPoint old_position, bool vertical, int size, int distance);
    void drawMap();
};

#endif

