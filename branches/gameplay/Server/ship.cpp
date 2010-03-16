#include "ship.h"

void Ship::applyActionMask(ClientAction newMask){
    actionMask = newMask;
}
UpdateObject Ship::makeUpdateObject(UpdateObject uo){
    uo.pos_ = position;
    uo.rotation_ = rotation;
    uo.id = id;
}
