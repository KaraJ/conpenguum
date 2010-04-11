#include <QtCore/QCoreApplication>
#include <iostream>
#include <QDomDocument>
#include <qfile.h>
#include <QTextStream>
#include <sstream>

#include "tiletypes.h"

int main(int argc, char *argv[])
{
    int width;
    int height;
    int tileSize;
    QCoreApplication a(argc, argv);
    if (argc < 3 || argc > 4) {
        std::cerr << "Usage: MapTranslator <types.xml> <map.tmx> [<map.xml>]" << std::endl;
    }

    QDomDocument typesDoc;
    QFile typesFile(argv[1]);
    if (!typesFile.open(QIODevice::ReadOnly)) {
        std::cerr << "Cannot open " << argv[1] << std::endl;
        return 1;
    }
    if (!typesDoc.setContent(&typesFile)) {
        std::cerr << "Unusable file " << argv[1] << std::endl;
        return 1;
    }
    typesFile.close();

    QDomDocument tmxDoc;
    QFile tmxFile(argv[2]);
    if (!tmxFile.open(QIODevice::ReadOnly)) {
        std::cerr << "Cannot open " << argv[2] << std::endl;
        return 1;
    }
    if (!tmxDoc.setContent(&tmxFile)) {
        std::cerr << "Unusable file " << argv[2] << std:: endl;
    }
    QDomElement map_e = tmxDoc.documentElement();

    // generate xml
    width = map_e.attribute("width").toInt();
    height = map_e.attribute("height").toInt();
    tileSize = map_e.attribute("tilewidth").toInt();
    TileTypes tileTypes(&typesDoc, &tmxDoc);

    QDomDocument doc("Map");
    QDomElement map = doc.createElement("map");
    map.setAttribute("width", width);
    map.setAttribute("height", height);
    map.setAttribute("tileSize", tileSize);
    QDomElement tile_e = map_e.elementsByTagName("layer").item(0).toElement().elementsByTagName("data").item(0).toElement().firstChild().toElement();
    TileType *type;
    std::stringstream sString;
    for (int y=height-1; y >= 0; --y) {
        for (int x=0; x < width; ++x) {
            int gid=tile_e.attribute("gid").toInt();
            if (gid > 0) {
                type = tileTypes.byGid(gid);
                if (type == NULL) {
                    std::cerr << "type(" << gid << ") == NULL!!! @ " << x << "x" << y << std::endl;
                }
                QDomElement tile = doc.createElement("tile");
                // tile
                tile.setAttribute("x", x);
                tile.setAttribute("y", y);
                // physics
                if (type->physics != "") {
                    QDomElement physics = doc.createElement("physics");
                    physics.setAttribute("hit", type->physics);
                    tile.appendChild(physics);
                }
                // graphics
                QDomElement graphics = doc.createElement("graphics");
                graphics.setAttribute("filename", type->filename);
                graphics.setAttribute("tileNumber", gid - type->firstGid);
                // add to tile
                tile.appendChild(graphics);
                map.appendChild(tile);
            }
            tile_e = tile_e.nextSibling().toElement();
        }
    }
    QDomNodeList spawn_l = map_e.elementsByTagName("objectgroup").item(0).toElement().elementsByTagName("object");
    for (int i=0; i < spawn_l.size(); ++i)
    {
        QDomElement spawn_e = spawn_l.item(i).toElement();
        QDomElement spawn = doc.createElement("spawn");
        spawn.setAttribute("x", spawn_e.attribute("x"));
        spawn.setAttribute("y", spawn_e.attribute("y"));
        spawn.setAttribute("width", spawn_e.attribute("width"));
        spawn.setAttribute("height", spawn_e.attribute("height"));
        QDomNodeList spawn_attribute_l = spawn_e.elementsByTagName("properties").item(0).toElement().elementsByTagName("property");
        for (int p=0; p < spawn_attribute_l.size(); ++p)
        {
            QDomElement spawn_attribute_e = spawn_attribute_l.item(p).toElement();
            if (spawn_attribute_e.attribute("name") == "team")
            {
                spawn.setAttribute("team", spawn_attribute_e.attribute("value"));
            }
        }
        map.appendChild(spawn);
    }
    doc.appendChild(map);
    if (argc > 3) {
        QFile xmlFile(argv[3]);
        if (!xmlFile.open(QIODevice::WriteOnly)) {
            std::cerr << "Unable to open " << argv[3] << " for writing" << std::endl;
        } else {
            QTextStream xmlStream(&xmlFile);
            xmlStream << doc.toString();
            xmlFile.close();
        }
    } else {
        std::cout << doc.toString().toStdString() << std::endl;
    }

    //return a.exec();
}
