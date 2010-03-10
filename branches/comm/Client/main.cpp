#include "main.h"
#include "comm/commclient.h"
#include "comm/data/clientaction.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	QResource::registerResource("GUI/menuitems.rcc");

	// insert main gfx window initilization here, which extends from BaseWindow

	//GameWindow mainWin = new GameWindow();
	BaseWindow mainWin;

	mainWin.setWindowTitle("Game Window");

	mainWin.show();
	int id;
	double totaltime = 0;
	int numsent = 0;
	int numRecv = 0;
	int numLost = 0;
	clock_t time;
	CommClient* client;
	client = CommClient::Instance();
	id = client->connect(argv[1], argv[2]);
	int max = atoi(argv[3]);
	for (int i = 0; i < max; i++)
	{
		ClientAction action(0);
		switch (rand() % 5) {
		case 0:
			action.setAccelerating();
			break;
		case 1:
			action.setFiring();
		case 2:
			action.setTurningLeft();
			break;
		case 3:
			action.setTurningRight();
			break;
		case 4:
			action.setTurningLeft();
			action.setTurningRight();
			break;
		}
		time = clock();
		client->sendAction(action);
		numsent++;
		while(1)
		{
			if(((clock() - time)/CLOCKS_PER_SEC) > 5)
			{
				numLost++;
				break;
			}
			if (client->hasNextUpdate())
			{
				numRecv++;
				UpdateObject update = client->nextUpdate();
				if (update.getActions().getObjectID() == id)
				{
					totaltime += (clock() - time);
					break;
				}
			}
		}
	}
	printf("Avg round trip time: %f\n", totaltime / numsent / CLOCKS_PER_SEC);
	printf("Total Lost: %d", numLost);
	fflush(stdout);

	return app.exec();
}

