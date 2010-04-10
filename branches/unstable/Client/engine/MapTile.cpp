#include "MapTile.h"

MapTile::MapTile(int texTileNum, int mapRow, int mapCol, int texTileSizeInPix, int texWidthInTiles, int texHeightInTiles)
{
    int texCol = texTileNum % texWidthInTiles;
    int texWidthInPix = texWidthInTiles * texTileSizeInPix;
    int texOffsetInPixX = texCol * texTileSizeInPix;
    texOffsetXStart_ = texOffsetInPixX / texWidthInPix;
    float tileWidthOffset = texTileSizeInPix / (float)texWidthInPix;
    texOffsetXEnd_ = texOffsetXStart_ + tileWidthOffset;

    int texRow = texTileNum / texWidthInTiles;
    int texHeightInPix = texHeightInTiles * texTileSizeInPix;
    int texOffsetInPixY = texRow * texTileSizeInPix;
    texOffsetYStart_ = texOffsetInPixY / texHeightInPix;
    float tileHeightOffset = texTileSizeInPix / (float)texHeightInPix;
    texOffsetYEnd_ = texOffsetYStart_ + tileHeightOffset;

    pos_.setX(mapCol * texTileSizeInPix);
    pos_.setY(mapRow * texTileSizeInPix);
}

MapTile::~MapTile()
{

}
