#include "Map.h"

#include "MapTile.h"

Map::Map(QString srcTexture, int tileSizeInPix, int texWidthInTiles, int texHeightInTiles)
    : texName_(srcTexture), tileSize_(tileSizeInPix)
{

}

void Map::addTile(int texTileNum, int row, int col)
{
    MapTile* tile = new MapTile(texTileNum, row, col);
    tiles_.push_back(tile);
}

Map::~Map()
{

}
