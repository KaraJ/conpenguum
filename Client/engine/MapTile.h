#ifndef MAPTILE_H_
#define MAPTILE_H_

#include <QString>
#include <QPoint>

class MapTile
{
public:
    MapTile(int texTileNum, int mapRow, int mapCol, int texTileSizeInPix, int texWidthInTiles, int texHeightInTiles);
    virtual ~MapTile();
    int getTextureOffsetXStart() { return texOffsetXStart_; }
    int getTextureOffsetYStart() { return texOffsetYStart_; }
    int getTextureOffsetXEnd() { return texOffsetXEnd_; }
    int getTextureOffsetYEnd() { return texOffsetYEnd_; }
    const QPoint& getPos() { return pos_; }
private:
    float texOffsetXStart_;
    float texOffsetYStart_;
    float texOffsetXEnd_;
    float texOffsetYEnd_;
    QPoint pos_;
};

#endif
