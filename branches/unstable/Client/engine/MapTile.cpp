#include "MapTile.h"

MapTile::MapTile(int id, QString srcTexture, int texTileSizeInPix, int texWidthInTiles, int texHeightInTiles)
    : srcTexture_(srcTexture), texTileSizeInPix_(texTileSizeInPix), texWidthInTiles_(texWidthInTiles), texHeightInTiles_(texHeightInTiles)
{
    int row = id / texWidthInTiles;
    int col = id % texWidthInTiles;
    texOffsetInPixX_ = row * texTileSizeInPix;
    texOffsetInPixY_ = col * texTileSizeInPix;
}

MapTile::~MapTile()
{

}
