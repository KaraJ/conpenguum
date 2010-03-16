#include "main.h"

#include "comm/data/clientaction.h"
#include "comm/data/updateobject.h"
#include "comm/commserver.h"
#include "comm/data/servermessage.h"

void SerializeTest();
void UDPTest();
void StressTest();

int main() {
	//SerializeTest();
	//UDPTest();
	StressTest();
	return 0;
}

void UDPTest() {
	CommServer::Instance()->init();
	while (true) {
		if (CommServer::Instance()->hasNextClientAction()) {
			ClientAction a = CommServer::Instance()->nextClientAction();
			a.print();
			UpdateObject o(a.getObjectID());
			o.setPosition(QPoint(5, 5));
			o.setRotation(10);
			o.getActions().setFiring();
			std::vector<int> ids;
			ids.push_back(a.getObjectID());
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

	a.serialise(&buffer);

	ClientAction b(buffer);
	delete buffer;

	buffer = 0;

	UpdateObject u(4);
	u.setPosition(QPoint(2345, 1432));
	u.setRotation(23);
	u.getActions().setTurningLeft();
	u.getActions().setAccelerating();
	u.getActions().setTurningRight();

	u.serialise(&buffer);

	UpdateObject w(buffer);
	delete buffer;
}

void StressTest() {
	int actionsRx = 0;
	int updatesPushed = 0;
	CommServer::Instance()->init();
	while (true) {
		if (CommServer::Instance()->hasNextClientAction()) {
			actionsRx++;
			ClientAction a = CommServer::Instance()->nextClientAction();
			UpdateObject o(a);
			std::vector<int> ids;
			ids.push_back(a.getObjectID());
			CommServer::Instance()->sendUpdateToAll(o);
			updatesPushed++;
		}
		while (CommServer::Instance()->hasNextServerMessage())
		{
			ServerMessage sm = CommServer::Instance()->nextServerMessage();
			printf("SM: %s\n", sm.GetData().c_str());
			if (sm.GetMsgType() == ServerMessage::MT_LOGIN)
			{
				sm.SetMsgType(ServerMessage::MT_INIT);
				CommServer::Instance()->sendServerMsg(sm);
			}
			else if (sm.GetMsgType() == ServerMessage::MT_LOGOUT)
			{
				printf("CA Rx: %d\nUO Tx: %d\n", actionsRx, updatesPushed);
			}
		}
	}
}
