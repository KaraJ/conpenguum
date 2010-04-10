#include "Map.h"

Map::Map(QString srcTexture, int tileSizeInPix, int texWidthInTiles, int texHeightInTiles)
    : texName_(srcTexture), tileSize_(tileSizeInPix), texWidthInTiles_(texWidthInTiles), texHeightInTiles_(texHeightInTiles)
{

}

void Map::addTile(int texTileNum, int mapRow, int mapCol)
{
    MapTile* tile = new MapTile(texTileNum, mapRow, mapCol, tileSize_, texWidthInTiles_, texHeightInTiles_);
    tiles_.push_back(tile);
}

Map::~Map()
{

}
