#ifndef MAPTILE_H_
#define MAPTILE_H_

#include <QString>

class MapTile
{
public:
    MapTile(int tileNum, int row, int col, QString srcTexture = QString("tiles.bmp"), int texTileSizeInPix = 16, int texWidthInTiles = 19, int texHeightInTiles = 10);
    virtual ~MapTile();
    int getTextureOffsetX() { return texOffsetX_; }
    int getTextureOffsetY() { return texOffsetY_; }
    int getTileSizeInPix() { return tileSizeInPix_; }
    QString getTextureName() { return texName_; }
    const QPoint& getPos() { return pos_; }
private:
    QString texName_;
    int texOffsetX_;
    int texOffsetY_;
    int tileSizeInPix_;
    QPoint pos_;
};

#endif
