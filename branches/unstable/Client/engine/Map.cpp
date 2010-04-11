#include "Map.h"

using namespace std;

Map::Map(QString filename)
{
    QDomDocument doc;
    int x, y;
    QFile file(filename);
    string fname = filename.toStdString();

    // open file
    if (!file.open(QIODevice::ReadOnly))
        Logger::LogNQuit("Could not open map file");

    // parse file
    if (!doc.setContent(&file))
        Logger::LogNQuit("Bad map file");
    file.close();

    // check XML
    QDomElement map_e = doc.documentElement();
    if (map_e.tagName() != "map")
        Logger::LogNQuit("Bad map format");

    // read map data
    int columns = map_e.attribute("width", "0").toInt();
    int rows = map_e.attribute("height", "0").toInt();
    int tileSize = map_e.attribute("tileSize", "1").toInt();

    // read tiles
    QDomNodeList tile_l = map_e.elementsByTagName("tile");
    for (int ti = 0; ti < tile_l.count(); ++ti)
    {
        QDomElement tile_e = tile_l.item(ti).toElement();
        QDomElement graphics_e = tile_e.elementsByTagName("graphics").item(0).toElement();
        x = tile_e.attribute("x", "0").toInt();
        y = tile_e.attribute("y", "0").toInt();
        int tileNum = graphics_e.attribute("tileNum").toInt();
        addTile(tileNum, y, x);
    }
}

void Map::addTile(int texTileNum, int mapRow, int mapCol)
{
    MapTile* tile = new MapTile(texTileNum, mapRow, mapCol);
    tiles_.push_back(tile);
}

Map::~Map()
{

}
