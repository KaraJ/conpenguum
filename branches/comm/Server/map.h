#ifndef _MAP_H
#define _MAP_H

#include <list>
#include "newtObjects.h"

class Tile {
protected:
    bool isWall;
    std::list<int> ships;
    std::list<Shot> shots;
public:
    Tile(int x, int y);
    bool is_wall();
    int numShips();
    int numShots;
    bool overlap(NewtObject object);
    void addShip(Ship ship);
    void addShot(Shot shot);
    void delShip(Ship ship);
    void delShot(Shot shot);
};

class Map {
protected:
    Tile map[1];
public:
    Map(int x, int y);
    void add_ship(/*Player player*/);
    void remove_ship(Ship ship);
    void moved(Ship ship);
    void moved(Shot shot);
};

#endif
