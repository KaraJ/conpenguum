#ifndef UPDATEOBJECT_H
#define UPDATEOBJECT_H

#include "clientaction.h"

class UpdateObject
{
public:
    UpdateObject(int clientID, int type) : rotation_(0), posX_(0), posY_(0), actions_(ClientAction(clientID, type)) {}

    inline int getRotation() const { return rotation_; }
    inline int getPosX() const { return posX_; }
    inline int getPosY() const { return posY_; }
    inline ClientAction getActions() { return actions_; }

    inline void setRotation(int rot) { rotation_ = rot; }
    inline void setPosition(int x, int y) { posX_ = x; posY_ = y; }
private:
    int rotation_;
    int posX_;
    int posY_;
    ClientAction actions_;
};

#endif
