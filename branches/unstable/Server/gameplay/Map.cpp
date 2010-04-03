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
    columns  = map_e.attribute("width", "0").toInt() - 1;
    rows = map_e.attribute("height", "0").toInt() - 1;
    tileSize = map_e.attribute("tileSize", "1").toInt();

    // create tiles array
    tiles=new Tile**[rows];
    for(int i = 0; i < rows; ++i)
    {
    	*(tiles + i)=new Tile*[columns];
    	for(int x = 0; x < columns; ++x)
    		*(tiles[i] + x) = new Tile();
    }

    // read tiles
    QDomNodeList tile_l = map_e.elementsByTagName("tile");
    for (int ti = 0; ti < tile_l.count(); ++ti)
    {
        QDomElement tile_e = tile_l.item(ti).toElement();
        QDomElement physics_e = tile_e.elementsByTagName("physics").item(0).toElement();
        x = tile_e.attribute("x", "0").toInt();
        y = tile_e.attribute("y", "0").toInt();

		//tiles[x][y];
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
--  FUNCTION:   Map::tile
--
--  DATE:       February 17, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile tile(int x, int y)
--              x : x position along grid of target tile
--              y : y position along grid of target tile
--
--  NOTES:      Returns the tile at the specified position.
--
--  RETURNS:    Tile at the specified position.
--
------------------------------------------------------------------------------*/
Tile *Map::tile(int x, int y)
{
    ensure(x, y);
    return tiles[x][y];
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
--  INTERFACE:  move(Ship *ship, QVector2D old_position, QVector2D new_position, int size)
--              Ship *ship : Pointer to the ship to move
--              QVector2D old_position : the previous position of the ship.
--              QVector2D new_position : the new position of the ship.
--              int size : The size of a ship
--
--  NOTES:      Moves the ship from its old tile to the new one.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::move(Ship *ship, QVector2D old_position, QVector2D new_position, double size)
{
	double radius = size / 2;

    double leftOld = PIX_TO_TILE(old_position.x() - radius);
    double rightOld = PIX_TO_TILE(old_position.x() + radius);
    double botOld = PIX_TO_TILE(old_position.y() - radius);
    double topOld = PIX_TO_TILE(old_position.y() + radius);

    double leftNew = PIX_TO_TILE(new_position.x() - radius);
    double rightNew = PIX_TO_TILE(new_position.x() + radius);
    double botNew = PIX_TO_TILE(new_position.y()- radius);
    double topNew = PIX_TO_TILE(new_position.y() + radius);

    for (int x = MIN(leftOld, leftNew); x <= MAX(rightOld, rightNew); ++x)
    {
        for (int y = MIN(botOld, botNew); y <= MAX(topOld, topNew); ++y)
        {
            if (x < leftOld || x > rightOld || y < botOld || y > topOld) // if in new position
            {
                if (x <= leftNew && x >= rightNew && y >= botOld && y <= topOld)
                    tile(x, y)->add(ship);
            }
            else // is in old position!
            {
                if (x < leftNew || x > rightNew || y < botNew || y > topNew) // if not in new position
                    tile(x, y)->remove(ship);
            }
        }
    }

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
    ensure(new_x, new_y);
    tile(new_x, new_y)->add(shot);
    tile(old_x, old_y)->remove(shot);
    clean(old_x, old_y);
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
    int x1 = PIX_TO_TILE(location.x());
    int x2 = PIX_TO_TILE(location.x() + size);
    int y1 = PIX_TO_TILE(location.y());
    int y2 = PIX_TO_TILE(location.y() + size);
    for (int x = x1; x < x2; ++x)
    {
        for (int y = y1; y <= y2; ++y)
        {
            ensure(x, y);
            tile(x, y)->add(ship);
        }
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
    ensure(x, y);
    tile(x, y)->add(shot);
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
    int x1 = PIX_TO_TILE(location.x());
    int x2 = PIX_TO_TILE(location.x() + size);
    int y1 = PIX_TO_TILE(location.y());
    int y2 = PIX_TO_TILE(location.y() + size);
    for (int x = x1; x < x2; ++x)
    {
        for (int y = y1; y <= y2; ++y)
        {
            tile(x, y)->remove(ship);
            clean(x, y);
        }
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
    tile(x, y)->remove(shot);
    clean(x, y);
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

    /*if (tiles[x][y] == NULL)
        return false;*/

    return tiles[x][y]->isWall();
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

	if (vertical)
	{
		if (distance > 0)
			endTile = PIX_TO_TILE(position.y() + radius + distance);
		else
			endTile = PIX_TO_TILE(position.y() - radius + distance);

		center = PIX_TO_TILE(position.x());
		start  = PIX_TO_TILE(position.x() - radius);
		end    = PIX_TO_TILE(position.x() + radius);

		if (isWall(center, endTile))
			return -distance;
		if ((isWall(start, endTile)))
			return -distance;
		if (isWall(end, endTile))
			return -distance;
	}
	else
	{
		if (distance > 0)
			endTile = PIX_TO_TILE(position.x() + radius + distance);
		else
			endTile = PIX_TO_TILE(position.x() - radius + distance);

		center = PIX_TO_TILE(position.y());
		start  = PIX_TO_TILE(position.y() - radius);
		end    = PIX_TO_TILE(position.y() + radius);

		if (isWall(center, endTile))
			return -distance;
		if (isWall(start, endTile))
			return -distance;
		if (isWall(end, endTile))
			return -distance;
	}

    return distance;    // no collision detected, can move full distance
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::ensure
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  void ensure(int x, int y)
--              x : x position on grid
--              y : y position on grid
--
--  NOTES:      ensures that there is a tile object at x,y (if tile already exists, nothing happens)
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Map::ensure(int x, int y)
{
    /*if (tiles[x][y] == NULL)
    {
        tiles[x][y] = new Tile(x, y);
    }*/
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Map::clean
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  void clean(int x, int y)
--              x : x position on grid
--              y : y position on grid
--
--  NOTES:      Cleans the specified coordinates. If the tile is empty (and not a wall), it is deleted.
--              This is used to minimize ram usage (which would otherwise escalate badly for larger maps)
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Map::clean(int x, int y)
{
    /*if (tiles[x][y] == NULL)
    {
        return; // tile is gone, nothing to do.
    }*/
    if (tiles[x][y]->empty())
    {
        return; // tile not emtpy, DO NOT CLEAN!
    }
    /*delete tiles[x][y];
    tiles[x][y] = NULL;*/
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
    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            std::cout << (isWall(i, j) ? "X" : "-");
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
            list2 = tile(x, y)->getShips();
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
            list2 = tile(x, y)->getShots();
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
    /*if (tiles[x][y] == NULL)
    {
        return false;
    }*/
    return (tile(x, y)->numShips() > 0);
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
    return tile(x, y)->getShips();
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
