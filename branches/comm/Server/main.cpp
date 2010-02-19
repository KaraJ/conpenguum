#include "main.h"

#include "comm/data/clientaction.h"
#include "comm/data/updateobject.h"

int main()
{
	//*******************
	//Testing the UDP Server
	UDPServer serv;
	serv.EchoMessage();
	//
	//******************
    BYTE* buffer = 0;
    size_t numBytes;

    ClientAction a(0);
    a.setTurningLeft();

    a.serialize(&buffer, numBytes);

    ClientAction b(buffer, numBytes);
    delete buffer;

    buffer = 0;

    UpdateObject u(20);
    u.setPosition(QPoint(2, 2));
    u.setRotation(2);
    u.getActions().setFiring();

    u.serialize(&buffer, numBytes);

    UpdateObject w(buffer, numBytes);
    delete buffer;

    return 0;
}
