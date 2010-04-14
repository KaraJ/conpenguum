#ifndef UPDATEOBJECT_H
#define UPDATEOBJECT_H

#include "clientaction.h"
#include "../globals.h"
#include <cstring>
#include <QPoint>
#include <iostream>

class UpdateObject
{
public:
    static const int serializeSize = 11;

    UpdateObject(int objID);
    UpdateObject(ClientAction& a);
    UpdateObject(BYTE* buffer);

    inline int getRotation() const { return rotation_; }
    inline QPoint getPos() const { return pos_; }
    inline ClientAction& getActions() { return actions_; }
    inline unsigned short getObjectId() { return actions_.getObjectId(); }

    inline void setRotation(int rot) { rotation_ = rot; }
    inline void setPosition(const QPoint& p) { pos_ = p; }
    void serialise(BYTE** buffer) const;
    void print(std::ostream& out = std::cout) const;

    int getHealth() const { return health_; }
    void setHealth(int hp) { health_ = hp; }
    int getShield() const { return shield_; }
    void setShield(int sh) { shield_ = sh; }
    int getShipType() const { return type_; }
    void setShipType(int t) { type_ = t; }

private:
    int rotation_;
    int health_, shield_, type_;
    QPoint pos_;
    ClientAction actions_;
};

#endif
