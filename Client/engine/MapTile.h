#ifndef MAPTILE_H_
#define MAPTILE_H_

#include <QString>
#include <QPoint>

class MapTile
{
public:
    MapTile(int texTileNum, int mapRow, int mapCol);
    virtual ~MapTile();
    const QPoint& getPos() { return pos_; }
    int getTileID() const { return tileID; }
private:
    int    tileID;
    QPoint pos_;
};

#endif
