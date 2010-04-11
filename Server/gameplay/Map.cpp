#include "Map.h"
#include "general.h"
#include <QString>
#include <QDomDocument>
#include <QFile>
#include <iostream>
#include "stdlib.h"
#include <QVector2D>

using namespace std;

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::Map
--
--  DATE:       February 17, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Map(QString filename)
--              filename : filename of the map xml file
--
--  NOTES:      Constructor that parses an XML file.
--
--  RETURNS:    Map object (constructor).
--
------------------------------------------------------------------------------*/
Map::Map(QString filename) : columns(0), rows(0), tileSize(1)
{
    QDomDocument doc;
    int x, y;
    QFile file(filename);

    // open file
    if (!file.open(QIODevice::ReadOnly))
    {
        cerr << "Cannot open file" << endl;
        return;
    }

    // parse file
    if (!doc.setContent(&file))
    {
        cerr << "Unusable file" << endl;
        file.close();
        return;
    }
    file.close();

    // check XML
    QDomElement map_e = doc.documentElement();
    if (map_e.tagName() != "map")
    {
        cerr << "Not a map element" << endl;
        return;
    }

    // read map data
    columns  = map_e.attribute("width", "0").toInt();
    rows = map_e.attribute("height", "0").toInt();
    tileSize = map_e.attribute("tileSize", "1").toInt();

    // create tiles array
    tiles=new Tile*[columns];
    for(int i = 0; i < columns; ++i)
        *(tiles + i) = new Tile[rows];

    // read tiles
    QDomNodeList tile_l = map_e.elementsByTagName("tile");
    for (int ti = 0; ti < tile_l.count(); ++ti)
    {
        QDomElement tile_e = tile_l.item(ti).toElement();
        QDomElement physics_e = tile_e.elementsByTagName("physics").item(0).toElement();
        x = tile_e.attribute("x", "0").toInt();
        y = tile_e.attribute("y", "0").toInt();
        if (physics_e.attribute("hit") == "bounce") {
            tiles[x][(rows-1)-y].setWall();
        }
    }

    // read spawns
    QDomNodeList spawn_l = map_e.elementsByTagName("spawn");
    SpawnArea spawn;
    for (int si=0; si < spawn_l.count(); ++si)
    {
        QDomElement spawn_e = spawn_l.item(si).toElement();
        spawn.x = spawn_e.attribute("x").toInt();
        spawn.y = spawn_e.attribute("y").toInt();
        spawn.width = spawn_e.attribute("width").toInt();
        spawn.height = spawn_e.attribute("height").toInt();
        spawn.team = spawn_e.attribute("team").toInt();
        spawns.push_back(spawn);
    }

    // seed rand(), used later in spawn selection
    srand(time(NULL));
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::move
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Shot *shto, QVector2D old_position, QVector2D new_position)
--              Shot *shot : Pointer to the shot to move
--              QVector2D old_position : the previous position of the shot.
--              QVector2D new_position : the new position of the shot.
--
--  NOTES:      Moves the shot from its old tile to the new one.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::move(Shot *shot, QVector2D old_position, QVector2D new_position)
{
    int old_x = PIX_TO_TILE(old_position.x());
    int old_y = PIX_TO_TILE(old_position.y());
    int new_x = PIX_TO_TILE(new_position.x());
    int new_y = PIX_TO_TILE(new_position.y());
    tiles[new_x][new_y].add(shot);
    tiles[old_x][old_y].remove(shot);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::add
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Ship *ship, QVector2D location, int size)
--              Ship *ship : Pointer to the ship to add
--              QVector2D location : location of the ship (so it can be added to the map).
--              size : Size of a ship.
--
--  NOTES:      Adds a new ship to the map.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::add(Ship *ship, QVector2D location, int size)
{
    int radius = size / 2;

    int x1 = PIX_TO_TILE(location.x() - radius);
    int x2 = PIX_TO_TILE(location.x() + radius);
    int y1 = PIX_TO_TILE(location.y() - radius);
    int y2 = PIX_TO_TILE(location.y() + radius);

    for (int x = x1; x <= x2; ++x)
    {
        for (int y = y1; y <= y2; ++y)
            tiles[x][y].add(ship);
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::add
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Shot *shot, QVector2D location, int size)
--              Shot *shot : Pointer to the shot to add
--              QVector2D location : location of the shot (so it can be added to the map).
--
--  NOTES:      Adds a new shot to the map.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::add(Shot *shot, QVector2D location)
{
    int x = PIX_TO_TILE(location.x());
    int y = PIX_TO_TILE(location.y());
    tiles[x][y].add(shot);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::remove
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Ship *ship, QVector2D location, int size)
--              Ship *ship : Pointer to the ship to remove
--              QVector2D location : location of the ship.
--              size : Size of a ship.
--
--  NOTES:      Removes a ship from the map.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::remove(Ship *ship, QVector2D location, int size)
{
    int radius = size / 2;

    int x1 = PIX_TO_TILE(location.x() - radius);
    int x2 = PIX_TO_TILE(location.x() + radius);
    int y1 = PIX_TO_TILE(location.y() - radius);
    int y2 = PIX_TO_TILE(location.y() + radius);

    for (int x = x1; x < x2; ++x)
    {
        for (int y = y1; y <= y2; ++y)
            tiles[x][y].remove(ship);
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::remove
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Shot *shot, QVector2D location, int size)
--              Shot *shot : Pointer to the shot to remove
--              QVector2D location : location of the shot.
--              size : Size of a shot.
--
--  NOTES:      Removes a shot from the map.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::remove(Shot *shot, QVector2D location)
{
    int x = PIX_TO_TILE(location.x());
    int y = PIX_TO_TILE(location.y());
    tiles[x][y].remove(shot);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::isWall
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  bool isWall(int x, int y)
--              x : x position in grid
--              y : y position in grid
--
--  NOTES:      checks if a tile is a wall.
--
--  RETURNS:    true if the tile is a wall, else false.
--
------------------------------------------------------------------------------*/
bool Map::isWall(int x, int y)
{
    if (x < 0 || y < 0 || x >= columns || y >= rows)
        return true;

    return tiles[x][y].isWall();
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::canMove
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  int canMove(QVector2D position, bool vertical, int size, int distance)
--              position : position of object we'd like to move (top-left corner)
--              vertical : true if trying to move vertically, false if moving horizontally
--              size : size of the object we are moving
--              distance : the distance we would like to try and move
--
--  NOTES:      calculates how far an object can move in any given direction (up to max of distance)
--
--  RETURNS:    The number of grid units the object can move or -1 if an error occured.
--
------------------------------------------------------------------------------*/

double Map::canMove(QVector2D position, bool vertical, double objSize, double distance)
{
    double radius = objSize / 2;
    //Leading edge of object
    double start, center, end, endTile;
    double xpos = position.x();
    double ypos = position.y();

    if (vertical)
    {
        if (distance > 0)
            endTile = PIX_TO_TILE(ypos + radius + distance);
        else
            endTile = PIX_TO_TILE(ypos - radius + distance);

        center = PIX_TO_TILE(xpos);
        start  = PIX_TO_TILE(xpos - radius);
        end    = PIX_TO_TILE(xpos + radius);
    }
    else
    {
        if (distance > 0)
            endTile = PIX_TO_TILE(xpos + radius + distance);
        else
            endTile = PIX_TO_TILE(xpos - radius + distance);


        center = PIX_TO_TILE(ypos);
        start  = PIX_TO_TILE(ypos - radius);
        end    = PIX_TO_TILE(ypos + radius);
    }

    if (endTile < 0)
        return -distance;

    if (isWall(center, endTile))
        return -distance;
    if (isWall(start, endTile))
        return -distance;
    if (isWall(end, endTile))
        return -distance;

    return distance;    // no collision detected, can move full distance
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::drawMap
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  void drawMap()
--
--  NOTES:      Draws the map to stdout (used for testing & debuging maps).
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Map::drawMap()
{
    for(int j = 0; j < rows; j++)
    {
        for(int i = 0; i < columns; i++)
        {
            std::cout << (isWall(i, j) ? "X" : ".");
        }
        std::cout << std::endl;
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::ships
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  std::list<Ship*> Map::ships(QVector2D center, int width=1024, int height=768)
--              center : center of the viewport
--              width : width of the viewport
--              height : height of the viewport
--
--  NOTES:      Returns all ships in a given viewport.
--              The viewport will have a margin of 50% of every side (quadrupaling total viewport area)
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
/*std::list<Ship*> Map::ships(QVector2D center, int width, int height)
{
    std::list<Ship*> list, list2;
    int left   = MAX(0       , Pix2Tile(center.x() - width));
    int right  = MIN(width-1 , Pix2Tile(center.x() + width));
    int bottom = MAX(0       , Pix2Tile(center.y() - width));
    int top    = MIN(height-1, Pix2Tile(center.x() + width));
    for (int x=left; x <= right; ++x)
    {
        for (int y=bottom; y <= top; ++x)
        {
            list2 = tiles[x][y].getShips();
            list.sort();
            list2.sort();
            list.merge(list2);
        }
    }
    list.unique();
    return list;
}*/

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::shots
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  std::list<Shot*> Map::shots(QVector2D center, int width=1024, int height=768)
--              center : center of the viewport
--              width : width of the viewport
--              height : height of the viewport
--
--  NOTES:      Returns all shots in a given viewport.
--              The viewport will have a margin of 50% of every side (quadrupaling total viewport area)
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
std::list<Shot*> Map::shots(QVector2D center, int width, int height)
{
    std::list<Shot*> list, list2;
    int left   = MAX(0       , PIX_TO_TILE(center.x() - width));
    int right  = MIN(width-1 , PIX_TO_TILE(center.x() + width));
    int bottom = MAX(0       , PIX_TO_TILE(center.y() - width));
    int top    = MIN(height-1, PIX_TO_TILE(center.x() + width));
    for (int x=left; x <= right; ++x)
    {
        for (int y=bottom; y <= top; ++x)
        {
            list2 = tiles[x][y].getShots();
            list.sort();
            list2.sort();
            list.merge(list2);
        }
    }
    list.unique();
    return list;
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::isWall
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  bool isWall(QVector2D location)
--              location : location to check for wall status
--
--  NOTES:      checks if a location is a wall.
--
--  RETURNS:    true if the location is a wall, else false.
--
------------------------------------------------------------------------------*/
bool Map::isWall(QVector2D location)
{
    return isWall(PIX_TO_TILE(location.x()), PIX_TO_TILE(location.y()));
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::hasShip
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  bool hasShip(QVector2D location)
--              location : location to check for ships
--
--  NOTES:      checks if a location's tile contains a ship.
--
--  RETURNS:    true if the location's tile contains a ship, else false.
--
------------------------------------------------------------------------------*/
bool Map::hasShip(QVector2D location)
{
    return hasShip(PIX_TO_TILE(location.x()), PIX_TO_TILE(location.y()));
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::hasShip
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  bool hasShip(int x, int y)
--              x : x co-ord of grid to check for ships
--              y : y co-ord of grid to check for ships
--
--  NOTES:      checks if a tile contains a ship.
--
--  RETURNS:    true if the tile contains a ship, else false.
--
------------------------------------------------------------------------------*/
bool Map::hasShip(int x, int y)
{
    return (tiles[x][y].numShips() > 0);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::ships
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  bool ships(QVector2D location)
--              location : location who's tile we need the ships from
--
--  NOTES:      gets all the ships in a given tile.
--
--  RETURNS:    std::list of ship pointers.
--
------------------------------------------------------------------------------*/
std::list<Ship*> Map::ships(QVector2D location)
{
    int x = PIX_TO_TILE(location.x());
    int y = PIX_TO_TILE(location.y());
    if (!hasShip(x, y))
    {
        return std::list<Ship*>();
    }
    return tiles[x][y].getShips();
}

QVector2D Map::getSpawn(int team, int size)
{
    // select random spawn area
    int teamCount = 0;
    SpawnArea teamSpawns[spawns.size()];
    SpawnArea area;
    for (size_t i=0; i < spawns.size(); ++i) {
        area = spawns.at(i);
        if (area.team == team && area.width >= size && area.height >= size) {
            teamSpawns[teamCount++] = area;
        }
    }
    if (teamCount == 0)
    {
        std::cerr << "ERROR: Could not locate a spawn for team " << team << ", spawning at 0,0" << std::endl;
        return QVector2D(0, 0);
    }
    area = teamSpawns[rand() % teamCount];

    int x = area.x;
    int y = area.y;
    if (area.width > size)
        x += rand() % (area.width - size);
    if (area.height > size)
        y += rand() % (area.height - size);

    // select random spot IN spawn area
    return QVector2D(x, y);
}
