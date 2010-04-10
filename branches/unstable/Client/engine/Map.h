#ifndef MAP_H_
#define MAP_H_

#include <QString>
#include <vector>

#include "MapTile.h"

class Map
{
public:
    Map(QString srcTexture = QString("tiles.bmp"), int tileSizeInPix = 16, int texWidthInTiles = 19, int texHeightInTiles = 10);
    virtual ~Map();
    const QString& getTexName() { return texName_; }
    int getTileSize() { return tileSize_; }
    std::vector<MapTile*> getTiles() { return tiles_; }
    void addTile(int texTileNum, int row, int col);
private:
    QString texName_;
    int tileSize_;
    std::vector<MapTile*> tiles_;
};

#endif
