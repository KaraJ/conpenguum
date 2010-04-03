#include "MapTile.h"

MapTile::MapTile(int x, int y, int id, QString srcTexture, int texTileSizeInPix, int texWidthInTiles, int texHeightInTiles)
    : x_(x), y_(y), srcTexture_(srcTexture), texTileSizeInPix_(texTileSizeInPix), texWidthInTiles_(texWidthInTiles), texHeightInTiles_(texHeightInTiles)
{

}

MapTile::~MapTile()
{

}
