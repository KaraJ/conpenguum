#ifndef UPDATEOBJECT_H
#define UPDATEOBJECT_H

#include "clientaction.h"
#include <cstring>
#include <QPoint>
#include <vector>

#define BYTE unsigned char //TODO: Move to shared space (also declared in message.h and clientaction.h)

class UpdateObject
{
public:
    UpdateObject(int clientID, int type) : rotation_(0), pos_(), actions_(ClientAction(clientID, type)) {}

    inline int getRotation() const { return rotation_; }
    inline QPoint getPos() const { return pos_; }
    inline ClientAction getActions() { return actions_; }

    inline void setRotation(int rot) { rotation_ = rot; }
    inline void setPosition(QPoint p) { pos_ = p; }
    bool serialize(char* buffer, size_t buffSize);
private:
    int rotation_;
    QPoint pos_;
    ClientAction actions_;
};

#endif
