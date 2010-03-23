#include "general.h"
#include "Tile.h"

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::Tile
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile(int new_x, int new_y)
--              new_x : tile x grid location
--              new_y : tile x grid location
--
--  NOTES:      Creates a new non-wall tile at position x,y.
--              Note: This does NOT add it to the map!
--                    The map is the only class that should be adding tiles.
--
--  RETURNS:    Tile object (constructor).
--
------------------------------------------------------------------------------*/
Tile::Tile(int new_x, int new_y):wall(false), x(new_x), y(new_y) {}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::Tile
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile(int new_x, int new_y, bool new_wall)
--              new_x : tile x grid location
--              new_y : tile x grid location
--              new_wall : true if tile should be a wall, else false
--
--  NOTES:      Creates a new tile at position x,y with posibility of being a wall.
--              Note: This does NOT add it to the map!
--                    The map is the only class that should be adding tiles.
--
--  RETURNS:    Tile object (constructor).
--
------------------------------------------------------------------------------*/
Tile::Tile(int new_x, int new_y, bool new_wall): wall(new_wall), x(new_x), y(new_y) {}


/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::isWall
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile()
--
--  NOTES:      Returns true if the tile is a wall, else false.
--
--  RETURNS:    true if the tile is a wall, else false.
--
------------------------------------------------------------------------------*/
bool Tile::isWall() {
    return wall;
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::add
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile(Ship *ship)
--              Ship *ship : ship to add to the tile
--
--  NOTES:      Adds a ship to the tile.
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Tile::add(Ship *ship) {
    ships.push_back(ship);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::add
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile(Shot *shot)
--              Shot *shot : ship to add to the tile
--
--  NOTES:      Adds a shot to the tile.
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Tile::add(Shot *shot) {
    shots.push_back(shot);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::remove
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile(Ship *ship)
--              Ship *ship : ship to remove from the tile
--
--  NOTES:      Removes a ship from the tile.
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Tile::remove(Ship *ship) {
    ships.remove(ship);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::remove
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Tile(Shot *shot)
--              Shot *shot : shot to remove from the tile
--
--  NOTES:      Removes a shot from the tile.
--
--  RETURNS:    void.
--
------------------------------------------------------------------------------*/
void Tile::remove(Shot *shot) {
    shots.remove(shot);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::numShips
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  numShips()
--
--  NOTES:      Counts the number of ships in the tile.
--
--  RETURNS:    The number of ships in the tile.
--
------------------------------------------------------------------------------*/
int Tile::numShips() {
    return ships.size();
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::numShots
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  numShots()
--
--  NOTES:      Counts the number of shots in the tile.
--
--  RETURNS:    The number of shots in the tile.
--
------------------------------------------------------------------------------*/
int Tile::numShots() {
    return shots.size();
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   Tile::empty
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  int empty()
--
--  NOTES:      Checks if the tile is empty (and not a wall).
--
--  RETURNS:    true if the tile is empty and not a wall, else false.
--
------------------------------------------------------------------------------*/
bool Tile::empty() {
    return (!isWall() && numShots() == 0 && numShips() == 0);
}
