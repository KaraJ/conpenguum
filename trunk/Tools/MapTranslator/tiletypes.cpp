#include <iostream>
#include "tiletypes.h"

TileTypes::TileTypes(QDomDocument *typesDoc, QDomDocument *tmxDoc)
{
    // types.xml
    TileType *type;
    QDomElement types_e = typesDoc->documentElement();
    if (types_e.tagName() != "tileTypes") {
        std::cerr << "types File invalid: " << types_e.tagName().toStdString() << std::endl;
        return;
    }
    QDomNodeList types_l = types_e.elementsByTagName("tileType");
    for (int ti=0; ti < types_l.count(); ++ti) {
        QDomElement te = types_l.item(ti).toElement();
        type = new TileType;
        type->name = te.attribute("name");
        type->width = te.attribute("width").toInt();
        type->height = te.attribute("height").toInt();
        type->physics = te.attribute("physics");
        type->src = te.attribute("src");
        type->filename = te.attribute("filename");
        type->firstGid = 0;
        add(type);
    }

    // map.tmx
    QDomElement tmx_e = tmxDoc->documentElement();
    if (tmx_e.tagName() != "map") {
        std::cerr << "tmx File Invalid" << std::endl;
        return;
    }
    QDomNodeList set_l = tmx_e.elementsByTagName("tileset");
    for (int set_i=0; set_i < set_l.count(); ++set_i) {
        QDomElement set_e = set_l.item(set_i).toElement();
        QString name=set_e.attribute("name");
        int found = false;
        TileType *type;
        for (std::list<TileType*>::iterator it=tileTypes.begin(); it != tileTypes.end(); ++it) {
            type = *it;
            if (type->name != name) {
                continue;
            }
            type->firstGid = set_e.attribute("firstgid").toInt();
            found = true;
        }
        if (!found) {
            std::cerr << "ERROR: Unable to find definition for " << name.toStdString() << std::endl;
        }
    }
}

TileType *TileTypes::byGid(int gid)
{
    TileType *type = NULL;
    for (std::list<TileType*>::iterator it=tileTypes.begin(); it != tileTypes.end(); ++it)
    {
        type = (*it);
        if (gid >= type->firstGid && gid < (type->firstGid + (type->width * type->height)))
        {
            return type;
        }
    }
    return NULL;
}

void TileTypes::add(TileType* tileType)
{
    tileTypes.push_back(tileType);
}

void TileTypes::printTypes()
{
    TileType *type;
    for (std::list<TileType*>::iterator it=tileTypes.begin(); it != tileTypes.end(); ++it)
    {
        type = *it;
        std::cout << "Tile " << type->name.toStdString() << "(" << type->firstGid << "): " << type->physics.toStdString() << " = " << type->width << "x" << type->height << std::endl;
    }
}
