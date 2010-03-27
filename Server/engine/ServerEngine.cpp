#include "ServerEngine.h"

#include "../../Core/comm/data/clientaction.h"
#include "../../Core/comm/data/servermessage.h"
#include "../../Core/comm/data/updateobject.h"
#include "../../Core/ConfigParser.h"

using namespace std;

/*------------------------------------------------------------------------------
 --
 -- CONSTRUCTOR: ServerEngine::ServerEngine()
 --
 -- DESIGNER: Brad Paugh
 --
 -- PROGRAMMER: Brad Paugh
 --
 -- REVISIONS:
 --
 -- NOTES:
 -- This constructor initializes the Comm Server
 --
 -----------------------------------------------------------------------------*/
ServerEngine::ServerEngine()
{
	ConfigParser cp;
	map<string, string> params;

	if (cp.Parse("server.conf", params) && params.find("tcp_port") != params.end())
	{
		commServer = CommServer::Instance();
		commServer -> init(params["tcp_port"]);
	}
	else
		cerr << "Invalid configuration file." << endl;

	gameState = new Frame("gameplay/map.xml");

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
	timer->start(32);
}

/*------------------------------------------------------------------------------
 --
 -- CONSTRUCTOR: BaseWindow::BaseWindow()
 --
 -- DESIGNER: Brad Paugh
 --
 -- PROGRAMMER: Brad Paugh
 --
 -- REVISIONS:
 --
 -- NOTES:
 -- This is the main loop for the server which handles all the
 -- Messages and actions that come from clients.
 --
 -----------------------------------------------------------------------------*/
void ServerEngine::timeout()
{
	vector<ClientAction> caBuff;
	vector<UpdateObject> uoBuff;

	while (commServer->hasNextServerMessage()) //Handle all control messages
	{
		ServerMessage sm = commServer->nextServerMessage();

		//user has logged in, add client id to ID vector
		if (sm.GetMsgType() == ServerMessage::MT_LOGIN)
		{
			cout << "client logged in" << endl;
			gameState->addShip(sm.GetClientID());
			gameState->spawnShip(sm.GetClientID());
			sm.SetMsgType(ServerMessage::MT_INIT); //TODO:Get score from gameplay
			sm.SetData("");
			commServer->sendServerMsg(sm);
		}
		if (sm.GetMsgType() == ServerMessage::MT_LOGOUT)
		{
			cout << "client logged out" << endl;
			gameState->removeShip(sm.GetClientID());
		}
		//receive chat message.. send to all clients
		if (sm.GetMsgType() == ServerMessage::MT_CHAT)
		{
			cout << "Received chat msg: " << sm.GetData() << endl;
			commServer->sendServerMsg(sm);
		}
	}

	while (commServer->hasNextClientAction()) //Grab all client actions
	{
		ClientAction ca = commServer->nextClientAction();
		cout << "Received client action" << endl;
		ca.print();
		cout.flush();
		caBuff.push_back(ca);
	}

	if (caBuff.size() > 0) //If anyone did anything...
		gameState->updateClientActions(caBuff);

	gameState->tick();
	uoBuff = gameState->ListShip2listUpdateObject();

	for (size_t i = 0; i < uoBuff.size(); ++i)
		commServer->sendUpdateToAll(uoBuff[i]);
}
