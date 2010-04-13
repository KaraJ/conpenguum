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
    TileTypes tileTypes(&typesDoc, &tmxDoc);

    QDomDocument doc("Map");
    QDomElement map = doc.createElement("map");
    map.setAttribute("width", width);
    map.setAttribute("height", height);
    QDomElement tile_e = map_e.elementsByTagName("layer").at(0).toElement().elementsByTagName("data").item(0).toElement().firstChild().toElement();
    TileType *type;
    std::stringstream sString;
    for (int y=height-1; y >= 0; --y) {
        for (int x=0; x < width; ++x) {
            int gid = tile_e.attribute("gid").toInt();
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
                if (gid <= MAX_BOUNCE_GID)
                {
                    QDomElement physics = doc.createElement("physics");
                    physics.setAttribute("hit", "bounce");
                    tile.appendChild(physics);
                }
                // graphics
                QDomElement graphics = doc.createElement("graphics");
                graphics.setAttribute("tileNumber", gid-1);
                // add to tile
                tile.appendChild(graphics);
                map.appendChild(tile);
            }
            tile_e = tile_e.nextSibling().toElement();
        }
    }
    QDomNodeList spawn_l = map_e.elementsByTagName("objectgroup").item(0).toElement().elementsByTagName("object");
    float spawn_ratio = FINAL_TILESIZE / EDITOR_TILESIZE;
    int spawn_x;
    int spawn_y;
    int spawn_w;
    int spawn_h;
    for (int i=0; i < spawn_l.size(); ++i)
    {
        QDomElement spawn_e = spawn_l.item(i).toElement();
        QDomElement spawn = doc.createElement("spawn");

        spawn_x = (int)(spawn_ratio * spawn_e.attribute("x").toInt());
        spawn_y = (int)(spawn_ratio * spawn_e.attribute("y").toInt());
        spawn_w = (int)(spawn_ratio * spawn_e.attribute("width").toInt());
        spawn_h = (int)(spawn_ratio * spawn_e.attribute("height").toInt());
        std::cerr << spawn_x << "," << spawn_y << " -> " << spawn_w << "x" << spawn_h << "(" << (FINAL_TILESIZE*height) - (spawn_y + spawn_h) << ")" << std::endl;

        spawn.setAttribute("x", spawn_x);
        spawn.setAttribute("y", (FINAL_TILESIZE*height) - (spawn_y + spawn_h));
        spawn.setAttribute("width", spawn_w);
        spawn.setAttribute("height", spawn_h);
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
