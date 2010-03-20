#include <iostream> // only used for testing
#include "frame.h"
#include "newtObjects.h"
#include "map.h"
#include "physics.h"
#include "../../Core/comm/data/clientaction.h"
#include "../.../Core/comm/data/updateobject.h"

#define VELOCITY_THRUST 2   // the velocity of a new thrust vector.
#define VELOCITY_SHOT   3   // the velocity of a shot.
#define VELOCITY_MAX    2   // the max velocity of a ship.
#define ROTATION_RATE   2   // how many degrees a ship rotates in a frame.
#define SHIPRADIUS      25  // the radius of a ships "tile".
#define SHIPSIZE        SHIPRADIUS*2
#define SHIP_HIT_DIST   625 // 25^2, the distance at which ships are hit.
#define TILE_SIZE       25  // the size of a side of a tile.
using namespace std;

/*-----------------------------------------------------------------------------
--  FUNCTION:   tick
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.2 - Calls updateShots and udateShips before incrementing the
--                     frame counter.
--              v0.1 - pinch of  code, mostly comments.
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
void Frame::tick(void){
    updateShots();
    updateShips();
    ++frameTimer;
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
void Frame::addShip(Ship newShip){
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
--              TASK: spawnShot should take the ship firing and spawn a shot
--                    according to the ships data, like rotation and type.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Frame::addShot(Shot newShot){
    // adds a shot to the shot list
    listShot.push_back(newShot);
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   getShip
--
--  DATE:       March 14, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  Ship getShip(int shipID)
--
--  NOTES:      returns the ship with the ID equal to shipID.
--
--  RETURNS:    Ship
--
------------------------------------------------------------------------------*/
list<Ship>::iterator Frame::getShip(int shipID){
    list<Ship>::iterator it;
    for(it = listShip.begin(); it != listShip.end(); ++it){
        if(it->id == shipID){
            return it;
        }
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   spawnShip
--
--  DATE:       March 14, 2010
--
--  REVISIONS:  v0.1 - pinch of  code, mostly comments.
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  spawnShip(int shipID)
--
--  NOTES:      Makes a ship active. Is will be spawned at a valid spawn point
--              and able to make actions as well as be destroyed.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Frame::spawnShip(int shipID){
    list<Ship>::iterator ship = getShip(shipID);
    QPoint spawnPoint(100,100); // map function to return a safe spawn point
    ship->active = true;
    ship->position = spawnPoint;
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   updateShips
--
--  DATE:       January 27, 2010
--
--  REVISIONS:  v0.2 - Untested collision.
--              v0.1 - pinch of  code, mostly comments.
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
void Frame::updateShips(void){
    list<Ship>::iterator it;
    int dist;
    for(it = listShip.begin(); it != listShip.end(); ++it){
        if(!(it->active)){
            continue;
        }
        // set new action mask
        // HERE
        dist = map.canMove(it->position, false, SHIPSIZE, it->vector.x());
        it->position.setX(it->position.x() + dist);
        dist = map.canMove(it->position, true, SHIPSIZE, it->vector.y());
        it->position.setX(it->position.y() + dist);

        if(it->actionMask.isAccelerating()){
            // thrust forward
            it->vector += rotVelToVec(it->rotation, VELOCITY_THRUST);
        }
        if(it->actionMask.isDecelerating()){
            // thrust reverse
            it->vector -= rotVelToVec(it->rotation, -VELOCITY_THRUST);
        }
        if(it->actionMask.isTurningRight()){
            // turn right
            it->rotation += ROTATION_RATE;
        }
        if(it->actionMask.isTurningLeft()){
            // turn left
            it->rotation += ROTATION_RATE;
        }
        if(it->actionMask.isFiring()){
            QPoint spawnVec, shotVec;
            spawnVec = rotVelToVec(it->rotation, SHIPRADIUS);
            shotVec =  rotVelToVec(it->rotation, VELOCITY_SHOT);
            Shot shot(it->position.x() + spawnVec.x(), it->position.y()
                + spawnVec.y(), shotVec.x(), shotVec.y(), (*it).id);
            addShot(shot);
        }
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
--  NOTES:      Updates all shots positions using their vectors. This is done in
--              frame because it has access to the Map and the Shot which both
--              need to be updated.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Frame::updateShots(void){
    list<Shot>::iterator it;
    for(it = listShot.begin(); it != listShot.end(); ++it){
        // add shot vec to pos
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
void Frame::printShips(void){
    list<Ship>::iterator it;
    for(it = listShip.begin(); it != listShip.end(); ++it){
        cout << (*it).id << ": P" << (*it).position.x()
            << ',' <<  (*it).position.y() << " V" <<(*it).vector.x()
            << ',' <<  (*it).vector.y() <<(it->active?" a":" d") <<
             " r" << it->rotation << endl;
    }
}

/*-----------------------------------------------------------------------------
--  FUNCTION:   dist2Points
--
--  DATE:       February 19, 2010
--
--  REVISIONS:  v0.1 - For testing only
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  dist2Points(QPoint point1, QPoint point2)
--
--  NOTES:      Given two points, returns the squared distance between them. For
--              testing only.
--
--  RETURNS:    Int value of the distance
--
------------------------------------------------------------------------------*/
int Frame::dist2Points(QPoint point1, QPoint point2){
    return (point1.x()-point2.x())*(point1.x()-point2.x()) +
            (point1.y()-point2.y())*(point1.y()-point2.y());
}

list<UpdateObject*> Frame::ListShip2listUpdateObject(){
	list<Ship>::iterator it;
	list<UpdateObject*> udList;	
	UpdateObject *uo = new UpdateObject(32);
	
	for(it = listShip.begin(); it != listShip.end(); ++it){
		uo = new UpdateObject(it->actionMask);
		uo->setRotation(it->rotation);
		uo->setPosition(it->position);
		udList.push_back(uo);
	}
	
	return udList;	
}
