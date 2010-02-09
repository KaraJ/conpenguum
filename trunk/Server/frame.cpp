#include <iostream> // only used for testing
#include "frame.hh"
#include "newtObjects.hh"
using namespace std;

/*-----------------------------------------------------------------------------
--  FUNCTION:   tick
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  tick(void)
--
--  NOTES:      Advances the frame one tick.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void frame::tick(void){
    updateShots();
    updateShips();
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   addShip
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  addShip(void)
--
--  NOTES:      Adds a ship to the ship list. Useful for adding new players.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void frame::addShip(ship newShip){
    // adds a ship to the ship list
    listShip.push_back(newShip);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   spawnShot
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  spawnShot(shot newShot)
--
--  NOTES:      Adds a shot to the shot list. Useful for when players shoot.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void frame::spawnShot(shot newShot){
    // adds a shot to the shot list
    listShot.push_back(newShot);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   updateShips
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  updateShips(void)
--
--  NOTES:      Updates all ships positions using their vectors.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void frame::updateShips(void){
    list<ship>::iterator it;
    for(it = listShip.begin(); it != listShip.end(); ++it){
        (*it).position += (*it).vector;
    }
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
--  NOTES:      Updates all shots positions using their vectors.
--
--  RETURNS:
--
------------------------------------------------------------------------------*/
void frame::updateShots(void){
    list<shot>::iterator it;
    for(it = listShot.begin(); it != listShot.end(); ++it){
        (*it).position += (*it).vector;
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   printShip
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  printShips(void)
--
--  NOTES:      **FOR TESTING** Prints the positions of all the ships.
--
--  FORMAT:     "<id>: <x>,<y>"
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void frame::printShips(void){
    list<ship>::iterator it;
    for(it = listShip.begin(); it != listShip.end(); ++it){
        cout << (*it).id << ": " << (*it).position.x()
            << ',' <<  (*it).position.y() << endl;
    }
}
