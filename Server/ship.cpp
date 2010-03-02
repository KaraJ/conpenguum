#include "ship.h"

void Ship::executeActionMask(){
    // based on the bitmask of actions, make changes
    // to the ship.

    /*
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
