#ifndef SHIP_H
#define SHIP_H

#include "newtObjects.h"

/*----------------------------------------------------------------------------
--
--  CLASSE:         ship
--
--  DATE:           January 27, 2010
--
--  REVISIONS:      v0.1 - basics, rest to be stubbed in
--
--  DESIGNER:       Gameplay/Physics Team
--
--  PROGREMMER:     Gameplay/Physics Team
--
--  NOTES:          A newtObject with rotation. The basis of a player
--                  controlled ship.
--
----------------------------------------------------------------------------*/
class Ship : public NewtObject
{
private:
public:
    int rotation;
    /*
    bit mask for the player actions
    */
private:
public:
    Ship(): rotation(0) {} // FOR TESTING ONLY
    Ship(int pX, int pY, int vX, int vY, int ID):
        NewtObject(pX, pY, vX, vY, ID){}
    int getRot(){ return rotation; }
    void executeActionMask(); // updates the ship based on the current action mask
};

#endif // SHIP_H
