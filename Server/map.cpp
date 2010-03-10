#include "map.h"
#include <QPoint>
#include <QString>

Map::Map(QString filename) {}

/*-----------------------------------------------------------------------------
--  FUNCTION:   tile
--
--  DATE:       February 17, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile tile(QPoint position)
--
--  NOTES:      Returns the tile at the specified position.
--
--  RETURNS:    Tile at the position.
--
------------------------------------------------------------------------------*/
Tile Map::tile(QPoint position) {
    return this->tiles[position.x() / this->tileSize][position.y() / this->tileSize];
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   move
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  move(Shot, QPoint)
--              Shot shot : The shot to move
--              QPoint old_position : the previous position of the ship.
--
--  NOTES:      Moves the ship from its old tile to the new one.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::move(Ship *ship, QPoint old_position, QPoint new_position, int size) {
}

void Map::move(Ship *shot, QPoint old_position, QPoint new_position) {
}

void Map::add(Ship *ship) {}
void Map::add(Shot *shot) {}
void Map::remove(Ship *ship) {}
void Map::remove(Shot *shot) {}
int Map::isWall(QPoint) {}
int Map::canMove(QPoint old_position, bool vertical, int size, int distance) {}
