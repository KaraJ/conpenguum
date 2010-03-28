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
    map.setAttribute("width", tileSize);
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
                QDomElement physics = doc.createElement("physics");
                physics.setAttribute("hit", type->physics);
                // graphics
                QDomElement graphics = doc.createElement("graphics");
                graphics.setAttribute("src", type->src);
                graphics.setAttribute("filename", type->filename);
                // Bottom Left Horizontal
                sString.str("");
                sString << (gid-type->firstGid) / type->width << "/" << type->width;
                graphics.setAttribute("blh", QString(sString.str().c_str()));
                // Bottom Left Vertical
                sString.str("");
                sString << (gid-type->firstGid) % type->width << "/" << type->height;
                graphics.setAttribute("blv", QString(sString.str().c_str()));
                // Top Right Horizontal
                sString.str("");
                sString << ((gid-type->firstGid) / type->width) + 1 << "/" << type->width;
                graphics.setAttribute("trh", QString(sString.str().c_str()));
                // Top Right Vertical
                sString.str("");
                sString << ((gid-type->firstGid) % type->width) + 1 << "/" << type->height;
                graphics.setAttribute("trv", QString(sString.str().c_str()));
                // add to tile
                tile.appendChild(physics);
                tile.appendChild(graphics);
                map.appendChild(tile);
            }
            tile_e = tile_e.nextSibling().toElement();
        }
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
