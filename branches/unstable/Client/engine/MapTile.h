#ifndef MAPTILE_H_
#define MAPTILE_H_

#include <QString>

class MapTile
{
public:
    MapTile(int x, int y, int id, QString srcTexture = QString("tiles.bmp"), int texTileSizeInPix = 16, int texWidthInTiles = 19, int texHeightInTiles = 10);
    virtual ~MapTile();
private:
    int x_;
    int y_;
    int texOffsetX_;
    int texOffsetY_;
    QString srcTexture_;
    int texTileSizeInPix_;
    int texWidthInTiles_;
    int texHeightInTiles_;
};

#endif
