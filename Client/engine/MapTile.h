#ifndef MAPTILE_H_
#define MAPTILE_H_

#include <QString>
#include <QPoint>

class MapTile
{
public:
    MapTile(int texTileNum, int row, int col);
    virtual ~MapTile();
    int getTextureOffsetX() { return texOffsetX_; }
    int getTextureOffsetY() { return texOffsetY_; }
    const QPoint& getPos() { return pos_; }
private:
    int texOffsetX_;
    int texOffsetY_;
    QPoint pos_;
};

#endif
