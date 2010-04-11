#ifndef MAP_H_
#define MAP_H_

#include <QFile>
#include <QString>
#include <vector>
#include <QDomDocument>
#include "../../Core/Logger.h"

#include "MapTile.h"

class Map
{
public:
    Map(QString filename);
    virtual ~Map();
    std::vector<MapTile*> &getTiles() { return tiles_; }
    void addTile(int texTileNum, int mapRow, int mapCol);
private:
    std::vector<MapTile*> tiles_;
};

#endif
