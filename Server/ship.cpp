#include "ship.h"

int Ship::currID = 0;

void Ship::applyActionMask(ClientAction newMask){
    actionMask = newMask;
}

