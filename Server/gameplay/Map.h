#ifndef _MAP_H
#define _MAP_H

#include <list>
#include <vector>
#include <sstream>
#include <string>
#include <exception>
#include "NewtObjects.h"
#include "Shot.h"
#include "Ship.h"
#include "Tile.h"
#include <QVector2D>

#define Pix2Tile(coord) ((coord) / tileSize)
#define Tile2Pix(tiles) ((tiles) * tileSize)

typedef struct
{
    int team;
    int x;
    int y;
    int width;
    int height;
} SpawnArea;

class Map
{
private :
    Tile ***tiles;
    std::vector<SpawnArea> spawns;
    int  width;    // map width in tiles
    int  height;   // map height in tiles
    int  tileSize; // length of tile edge in pixels
    Tile *tile(int x, int y);    // get by grid coord
    void ensure(int x, int y);  // ensure grid location has a tile
    void clean(int x, int y);   // remove free tile memory if empty (saves LOTS of ram!!!)
    bool isWall(int x, int y);  // checks if grid coords has a wall tile
public:
    Map(QString filename);
    void add(Ship *ship, QVector2D location, int size);
    void add(Shot *shot, QVector2D location);
    void remove(Ship *ship, QVector2D location, int size);
    void remove(Shot *shot, QVector2D location);
    void move(Ship *ship, QVector2D old_position, QVector2D new_position, int size);
    void move(Shot *shot, QVector2D old_position, QVector2D new_position);
    double canMove(QVector2D old_position, bool vertical, int size, double distance);
    //std::list<Ship*> ships(QVector2D, int width=1024, int height=768);
    std::list<Shot*> shots(QVector2D, int width=1024, int height=768);
    void drawMap();
    bool isWall(QVector2D location);
    bool hasShip(QVector2D location);
    bool hasShip(int, int);
    std::list<Ship*> ships(QVector2D location);
    QVector2D getSpawn(int team, int size);
};

#endif

