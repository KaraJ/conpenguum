#ifndef TILETYPES_H
#define TILETYPES_H

#include <list>
#include <QString>
#include <QDomDocument>

#define MAX_BOUNCE_GID 189

typedef struct {
    QString name;
    int width;
    int height;
    QString physics;
    QString filename;
    int firstGid;
} TileType;

class TileTypes
{
private:
    std::list<TileType*> tileTypes;
    void add(TileType*);
public:
    TileTypes(QDomDocument*, QDomDocument*);
    TileType *byGid(int gid);
    TileType *byName(QString);
    void printTypes();
};

#endif // TILETYPES_H
