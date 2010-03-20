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
    static const int serializeSize = 6;

    UpdateObject(int objID);
    UpdateObject(ClientAction& a);
    UpdateObject(BYTE* buffer);

    inline int getRotation() const { return rotation_; }
    inline QPoint getPos() const { return pos_; }
    inline ClientAction& getActions() { return actions_; }
    inline unsigned short getObjectId() { return actions_.getObjectID(); }

    inline void setRotation(int rot) { rotation_ = rot; }
    inline void setPosition(const QPoint& p) { pos_ = p; }
    void serialise(BYTE** buffer) const;
    void print(std::ostream& out = std::cout);
private:
    int rotation_;
    QPoint pos_;
    ClientAction actions_;
};

#endif
