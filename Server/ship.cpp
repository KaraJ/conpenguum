#include "ship.h"

void Ship::applyActionMask(ActionMask newMask){
    actionMask = newMask;
}
UpdateObject Ship::makeUpdateObject(UpdateObject uo){
    uo.pos_ = this.position;
    uo.rotation_ = this.rotation;
    uo.id = this.id;
}
