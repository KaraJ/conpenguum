#include "main.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#if 1
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(menuitems);

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
