#include "Ship.h"

Ship::Ship(size_t clientID, std::string ship) : NewtObject(0, 0, 0, 0, clientID),
	rotation(0), actionMask(clientID), active(false), shotCooldown(0),
	shieldCooldown(1), deathCooldown(0), health(100), shield(100), shipType(ship)
{
	currentShot = 0;
}

int Ship::getNextShotID()
{
    int nextShotID = MAX_CLIENTS + id * 10 + currentShot++;

    if(currentShot > 9)
        currentShot = 0;

    return nextShotID;
    
}
