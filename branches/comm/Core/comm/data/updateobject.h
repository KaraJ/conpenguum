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
    UpdateObject(int clientID) : rotation_(0), pos_(), actions_(ClientAction(clientID)) {}
    UpdateObject(BYTE* buffer, size_t buffSize);

    inline int getRotation() const { return rotation_; }
    inline QPoint getPos() const { return pos_; }
    inline ClientAction& getActions() { return actions_; }

    inline void setRotation(int rot) { rotation_ = rot; }
    inline void setPosition(const QPoint& p) { pos_ = p; }
    void serialize(BYTE** buffer, size_t& buffSize);
    void print(std::ostream& out = std::cout);
private:
    int rotation_;
    QPoint pos_;
    ClientAction actions_;
};

#endif
