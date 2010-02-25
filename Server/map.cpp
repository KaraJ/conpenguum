#include "map.h"
#include <QPoint>

/*-----------------------------------------------------------------------------
--  FUNCTION:   tileContents
--
--  DATE:       February 17, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile tileContents(QPoint position)
--
--  NOTES:      Returns the tile at the passed position.
--
--  RETURNS:    Tile at the position.
--
------------------------------------------------------------------------------*/
Tile Map::tile(QPoint position){
    int tileX, tileY, pos;
    tileX = position.x() % 25;
    tileX = position.y() % 25;
    if(tileX > width || tileY > height){
        // error handle
    }
    pos = tileY*width + tileX;
    return map[pos];
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   updateShots
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  updateShots(void)
--
--  NOTES:      Updates all shots positions using their vectors. This is done in
--              frame because it has access to the Map and the Shot which both
--              need to be updated. Only changes if the shot has entered a new
--              tile.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Map::move(Shot shot){

}
