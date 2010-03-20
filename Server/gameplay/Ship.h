#ifndef SHIP_H
#define SHIP_H

#include "NewtObjects.h"
#include "../../Core/comm/data/clientaction.h"

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
	static int currID;
public:
    int rotation;
    ClientAction actionMask;
    bool active;
private:
	int nextID(){return currID++;}
public:
    Ship():NewtObject(0, 0, 0, 0, nextID()), rotation(0), actionMask(id), active(false){}
    int getRot(){ return rotation; }
    void applyActionMask(ClientAction newMask); // updates the ship based on the current action mask
};

#endif // SHIP_H
