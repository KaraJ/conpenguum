#ifndef MAP_H_
#define MAP_H_

#include <QString>
#include <vector>

#include "MapTile.h"

class Map
{
public:
    Map();
    virtual ~Map();
    std::vector<MapTile*> &getTiles() { return tiles_; }
    void addTile(int texTileNum, int mapRow, int mapCol);
private:
    std::vector<MapTile*> tiles_;
};

#endif
