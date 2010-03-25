#include "main.h"

//TODO: Delete this
#include "../../Core/comm/data/updateobject.h"

#if 1
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(menuitems);

/*    UpdateObject update(23);
    QPoint pos(42321, 123);
    update.setPosition(pos);
    update.setRotation(94);
    update.getActions().setAccelerating();
    update.getActions().setDecelerating();
    update.getActions().setFiring();
    update.getActions().setTurningLeft();
    update.getActions().setTurningRight();
    update.print();
    BYTE* buff;
    update.serialise(&buff);
    UpdateObject update2(buff);
    update2.print();*/

    Panel *panel = new Panel();
    panel->setFocus();
    panel->show();

    return app.exec();
}

//TCP Client Test
#else
void *ReadThread(void*)
{
	while (true)
	{
		if (CommClient::Instance()->hasNextServerMessage())
		{
			ServerMessage m = CommClient::Instance()->nextServerMessage();
			if (m.GetMsgType() == ServerMessage::MT_FULL)
			{
				printf("Server is full\n");
				exit(0);
			}
			printf("ID: %d\nType: %d\nMsg: %s\n", m.GetClientID(), m.GetMsgType(), m.GetData().c_str());
		}
	}
	return NULL;
}
int main()
{
	pthread_t thread;
	printf("--Client--\n");
	CommClient::Instance()->connect("User", "127.0.0.1");
	pthread_create(&thread, NULL, ReadThread, NULL);
	string line;
	while (getline(cin, line))
	{
		if (line == "quit")
			break;
		CommClient::Instance()->sendServerMsg(line);
	}
	return 0;
}
#endif
