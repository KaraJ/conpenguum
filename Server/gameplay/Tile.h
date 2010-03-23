#ifndef _TILE_H
#define _TILE_H

#include <list>
#include "Ship.h"
#include "Shot.h"


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
};

#endif
