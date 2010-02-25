#include "main.h"

#include "comm/data/clientaction.h"
#include "comm/data/updateobject.h"

void SerializeTest();
void UDPServerTest();

int main()
{
    //UDPServerTest();
	SerializeTest();
    return 0;
}

void UDPServerTest()
{
    UDPServer serv;
    serv.EchoMessage();
}

void SerializeTest()
{
    BYTE* buffer = 0;
        size_t numBytes;

        ClientAction a(31);
    a.setTurningLeft();
    a.setAccelerating();
    a.setFiring();
    a.setTurningRight();

    a.serialize(&buffer, numBytes);

    ClientAction b(buffer, numBytes);
    delete buffer;

    buffer = 0;

    UpdateObject u(4);
    u.setPosition(QPoint(2345, 1432));
    u.setRotation(23);
    u.getActions().setTurningLeft();
    u.getActions().setAccelerating();
    u.getActions().setTurningRight();

    u.serialize(&buffer, numBytes);

    UpdateObject w(buffer, numBytes);
    delete buffer;
}
