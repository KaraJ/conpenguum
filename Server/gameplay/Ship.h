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
public:
    int rotation;
    ClientAction actionMask;
    bool active;
    int currentShot;
    int shotCooldown;
    int shieldCooldown;
    int deathCooldown;
    int health;
    int shield;

public:
    Ship(size_t clientID);
    int getRot() { return rotation; }
    void applyActionMask(ClientAction newMask) { actionMask = newMask; }
    int getNextShotID();
};

#endif // SHIP_H
