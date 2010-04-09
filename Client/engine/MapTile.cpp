#include "MapTile.h"

MapTile::MapTile(int id, int row, int col, QString srcTexture, int texTileSizeInPix, int texWidthInTiles, int texHeightInTiles)
    : srcTexture_(srcTexture), texTileSizeInPix_(texTileSizeInPix)
{
    int texRow = id / texWidthInTiles;
    int texCol = id % texWidthInTiles;
    int texWidthInPix = texWidthInTiles * texTileSizeInPix;
    int texHeightInPix = texHeightInTiles * texTileSizeInPix;
    int texOffsetInPixX = texRow * texTileSizeInPix;
    int texOffsetInPixY = texCol * texTileSizeInPix;
    texOffsetX_ = texOffsetInPixX / textWidthInPix;
    texOffsetY_ = texOffsetInPixY / texHeightInPix;

    pos_.setX(col * tileSizeInPix_);
    pos_.setY(row * tileSizeInPix_);
}

MapTile::~MapTile()
{

}
