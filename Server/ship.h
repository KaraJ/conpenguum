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
#include "clientaction.h"

struct UpdateObject
{
    int rotation_;
    QPoint pos_;
    int id;
};

class Ship : public NewtObject
{
private:
public:
    int rotation;
    ClientAction actionMask;
    bool active;
private:
public:
    Ship(int pX, int pY, int vX, int vY, int ID):
    NewtObject(pX, pY, vX, vY, ID), rotation(0), actionMask(ID), active(false){}
    int getRot(){ return rotation; }
    void applyActionMask(ClientAction newMask); // updates the ship based on the current action mask
    UpdateObject makeUpdateObject(UpdateObject uo);
};

#endif // SHIP_H

