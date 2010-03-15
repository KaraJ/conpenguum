#include <iostream> // only used for testing
#include "frame.h"
#include "newtObjects.h"
#include "map.h"
#include "physics.h"

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
    QPoint spawnPoint(100,100); // map function to return a safe spawn point
    getShip(shipID)->active = true;
    getShip(shipID)->position = spawnPoint;
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
        dist = map.canMove(it->position, false, SHIPSIZE, it->vector.x());
        cout << dist  << " " << it->vector.x() << endl;

        if(it->actionMask.isAccelerating()){
            // thrust forward
            it->vector += rotVelToVec(it->rotation, VELOCITY_THRUST);
        }
        if(it->actionMask.isDecelerating()){
            // thrust reverse
            it->vector -= rotVelToVec(it->rotation, -VELOCITY_THRUST);
        }
        if(it->actionMask.isTurningRight()){
            it->rotation += ROTATION_RATE;
        }
        if(it->actionMask.isTurningLeft()){
            it->rotation += ROTATION_RATE;
        }
        if(it->actionMask.isFiring()){
            QPoint spawnVec, shotVec;
            spawnVec = rotVelToVec((*it).rotation, SHIPRADIUS);
            shotVec =  rotVelToVec((*it).rotation, VELOCITY_SHOT);
            Shot shot((*it).position.x() + spawnVec.x(), (*it).position.y()
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
--  FUNCTION:   updateShips
--
--  DATE:       February 17, 2010
--
--  REVISIONS:  v0.1 - For testing only
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  updateShips(bool thrustF,bool thrustR, bool rotL,
--                  bool rotR, bool fire)
--
--  NOTES:      Updates all ships positions using their vectors. Than moves all
--              ships using the same user input data.
--
--  RETURNS:    void
--
------------------------------------------------------------------------------*/
void Frame::updateShips(bool thrustF,bool thrustR,
        bool rotL, bool rotR, bool fire){
/*    list<Ship>::iterator it;
    for(it = listShip.begin(); it != listShip.end(); ++it){
        // move the ship in the x axis
        (*it).position.setX((*it).vector.x());
        // if moving into a new tile
        if(map.tile((*it).position).isWall()){
            if((*it).vector.x() > 0){
                (*it).position.setX((*it).position.x() - (((*it).position.x()
                    + (*it).vector.x()) % TILE_SIZE));
            }
            else{
                (*it).position.setX((*it).position.x() + (((*it).position.x()
                    + (*it).vector.x()) % TILE_SIZE));
            }
        }
        // move the ship in the y axis
        (*it).position.setY((*it).vector.y());
        // if moving into a new tile
        if(map.tile((*it).position).isWall()){
            if((*it).vector.y() > 0){
                (*it).position.setY((*it).position.y() - (((*it).position.y()
                    + (*it).vector.y()) % TILE_SIZE));
            }
            else{
                (*it).position.setX((*it).position.x() + (((*it).position.x()
                    + (*it).vector.x()) % TILE_SIZE));
            }
        }
        if(thrustF){
            // thrust forward
            (*it).vector += rotVelToVec((*it).rotation, VELOCITY_THRUST);
        }
        if(thrustR){
            // thrust reverse
            (*it).vector += rotVelToVec((*it).rotation, VELOCITY_THRUST);
        }
        if(rotL){
            (*it).rotation -= ROTATION_RATE;
        }
        if(rotR){
            (*it).rotation += ROTATION_RATE;
        }
        if(fire){
            QPoint spawnVec, shotVec;
            spawnVec = rotVelToVec((*it).rotation, SHIPRADIUS);
            shotVec =  rotVelToVec((*it).rotation, VELOCITY_SHOT);
            Shot shot((*it).position.x() + spawnVec.x(), (*it).position.y()
                + spawnVec.y(), shotVec.x(), shotVec.y(), (*it).id);
            spawnShot(shot);
        }
    }
    */
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
