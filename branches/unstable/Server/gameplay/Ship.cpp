#include "Ship.h"

void Ship::applyActionMask(ClientAction newMask)
{
    actionMask = newMask;
}

int Ship::getNextShotID(){
    int nextShotID = 31 + id*10 + currentShot++;
    if(currentShot > 9){
        currentShot = 0;
    }
    return nextShotID;
    
}
