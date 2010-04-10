#include "Map.h"

Map::Map()
{

}

void Map::addTile(int texTileNum, int mapRow, int mapCol)
{
    MapTile* tile = new MapTile(texTileNum, mapRow, mapCol);
    tiles_.push_back(tile);
}

Map::~Map()
{

}
