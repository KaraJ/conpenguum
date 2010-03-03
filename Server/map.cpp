#include "map.h"
#include <QPoint>

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
Tile Map::tile(QPoint position){
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
void Map::move(Shot shot, QPoint old_position){
    int old_dimensions[4];
    int new_dimensions[4];
    int half_size = shot.size/2;
    float overSize = 1.0 / this->tileSize;

    old_dimensions = {
        (old_position.x() - half_size) * oldSize,
        (old_position.x() + half_size) * oldSize,
        (old_position.y() - half_size) * oldSize,
        (old_position.y() + half_size) * oldSize
    };
    new_dimensions = {
        (ship.position.x() - half_size) * oldSize,
        (ship.position.x() + half_size) * oldSize,
        (ship.position.y() - half_size) * oldSize,
        (ship.position.y() + half_size) * oldSize
    };
    for (int i=old_dimensions[0]; i < =
    this->tile(old_position).remove(shot);
    this->tile(shot.position).add(shot);
}
