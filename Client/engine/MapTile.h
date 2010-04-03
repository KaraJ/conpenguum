#ifndef MAPTILE_H_
#define MAPTILE_H_

#include <QString>

class MapTile
{
public:
    MapTile(int id, QString srcTexture = QString("tiles.bmp"), int texTileSizeInPix = 16, int texWidthInTiles = 19, int texHeightInTiles = 10);
    public int getTextureOffsetX() { return texOffsetInPixX_; }
    public int getTextureOffsetY() { return texOffsetInPixY_; }
    public QString getTextureName() { return texName_; }
    virtual ~MapTile();
private:
    QString texName_;
    int texOffsetInPixX_;
    int texOffsetInPixY_;
    int texTileSizeInPix_;
    int texWidthInTiles_;
    int texHeightInTiles_;
};

#endif
