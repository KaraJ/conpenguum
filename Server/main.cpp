#include "main.h"

#include "comm/data/clientaction.h"
#include "comm/data/updateobject.h"
#include "comm/commserver.h"

void SerializeTest();
void UDPTest();

int main() {
	//SerializeTest();
	UDPTest();
	return 0;
}

void UDPTest() {
	CommServer::Instance()->init();
	while (true) {
		if (CommServer::Instance()->hasNextClientAction()) {
			ClientAction a = CommServer::Instance()->nextClientAction();
			a.print();
			UpdateObject o(a.getClientID());
			o.setPosition(QPoint(5,5));
			o.setRotation(10);
			o.getActions().setFiring();
			std::vector<int> ids;
			ids.push_back(a.getClientID());
			CommServer::Instance()->sendUpdate(o, ids);
		}
	}
}

void SerializeTest() {
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
