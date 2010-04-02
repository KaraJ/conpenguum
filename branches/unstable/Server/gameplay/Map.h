#ifndef _MAP_H
#define _MAP_H

#include <QPoint>
#include <list>
#include <vector>
#include <sstream>
#include <string>
#include <exception>
#include "NewtObjects.h"
#include "Shot.h"
#include "Ship.h"
#include "Tile.h"

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
    void add(Ship *ship, QPoint location, int size);
    void add(Shot *shot, QPoint location);
    void remove(Ship *ship, QPoint location, int size);
    void remove(Shot *shot, QPoint location);
    void move(Ship *ship, QPoint old_position, QPoint new_position, int size);
    void move(Shot *shot, QPoint old_position, QPoint new_position);
    int canMove(QPoint old_position, bool vertical, int size, int distance);
    //std::list<Ship*> ships(QPoint, int width=1024, int height=768);
    std::list<Shot*> shots(QPoint, int width=1024, int height=768);
    void drawMap();
    bool isWall(QPoint location);
    bool hasShip(QPoint location);
    bool hasShip(int, int);
    std::list<Ship*> ships(QPoint location);
    QPoint getSpawn(int team, int size);
};

#endif

