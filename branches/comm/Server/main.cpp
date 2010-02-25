#include "main.h"

#include "comm/data/clientaction.h"
#include "comm/data/updateobject.h"

void SerializeTest();

int main()
{
    SerializeTest();
    return 0;
}

void SerializeTest()
{
    BYTE* buffer = 0;

    ClientAction a(31);
    a.setTurningLeft();
    a.setAccelerating();
    a.setFiring();
    a.setTurningRight();

    a.serialize(&buffer);

    ClientAction b(buffer);
    delete buffer;

    buffer = 0;

    UpdateObject u(4);
    u.setPosition(QPoint(2345, 1432));
    u.setRotation(23);
    u.getActions().setTurningLeft();
    u.getActions().setAccelerating();
    u.getActions().setTurningRight();

    u.serialize(&buffer);

    UpdateObject w(buffer);
    delete buffer;
}
