#include "ServerEngine.h"

#include "../../Core/comm/data/clientaction.h"
#include "../../Core/comm/data/servermessage.h"
#include "../../Core/comm/data/updateobject.h"
#include "../../Core/ConfigParser.h"

using namespace std;

ServerEngine *ServerEngine::instance = 0;

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
ServerEngine::ServerEngine() : commServer(0), gameState(0)
{
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

bool ServerEngine::Start()
{
	ConfigParser cp;
	map<string, string> params;

	signal(SIGINT, Shutdown);

	if (cp.Parse("server.conf", params) && params.find("tcp_port") != params.end())
	{
		commServer = CommServer::Instance();
		commServer -> init(params["tcp_port"]);
	}
	else
	{
		cerr << "Invalid configuration file." << endl;
		return false;
	}

	gameState = new Frame("gameplay/map.xml");
	srand(time(NULL));
	timer->start(32);
	return true;
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
			if (isNameUsed(sm.GetData()))
			{
				sm.SetMsgType(ServerMessage::MT_INIT);
				sm.SetData("FULL");
				commServer->sendServerMsg(sm);
			}
			else
			{
				ostringstream oss;
				cout << "client logged in" << endl;
				gameState->addShip(sm.GetClientID());
				gameState->spawnShip(sm.GetClientID());
				playerList.push_back(Player(sm.GetClientID(), sm.GetData()));
				ScoreBoard::Instance()->addPlayer(sm.GetClientID(), sm.GetData());

				oss << "* " << sm.GetData() << " has joined the game *";
				sm.SetMsgType(ServerMessage::MT_CHAT);
				sm.SetData(oss.str());
				commServer->sendServerMsgToAll(sm);

				sm.SetData("");
				sm.SetMsgType(ServerMessage::MT_INIT);
				commServer->sendServerMsg(sm);
				sendScores();
			}
		}
		if (sm.GetMsgType() == ServerMessage::MT_LOGOUT)
		{
			ostringstream oss;
			cout << "client logged out" << endl;
			gameState->removeShip(sm.GetClientID());
			for (vector<Player>::iterator it = playerList.begin(); it != playerList.end(); ++it)
			{
				if (it->getId() == (int)sm.GetClientID())
				{
					oss << "* " << getPlayerName(sm.GetClientID()) << " has left the game *";
					sm.SetMsgType(ServerMessage::MT_CHAT);
					sm.SetData(oss.str());
					commServer->sendServerMsgToAll(sm);
					ScoreBoard::Instance()->removePlayer(it->getId());
					playerList.erase(it);
					sendScores();
					break;
				}
			}
		}
		//receive chat message.. send to all clients
		if (sm.GetMsgType() == ServerMessage::MT_CHAT)
		{
			ostringstream oss;
			cout << "Received chat msg: " << sm.GetData() << endl;
			oss << "<" << getPlayerName(sm.GetClientID()) << "> " << sm.GetData();
			sm.SetData(oss.str());
			commServer->sendServerMsgToAll(sm);
		}
	}

	while (commServer->hasNextClientAction()) //Grab all client actions
	{
		ClientAction ca = commServer->nextClientAction();
		//cout << "Received client action" << endl;
		//ca.print();
		//cout.flush();
		caBuff.push_back(ca);
	}

	if (caBuff.size() > 0) //If anyone did anything...
		gameState->updateClientActions(caBuff);

	list<Event> events = gameState->tick();
	for (list<Event>::iterator it = events.begin(); it != events.end(); ++it)
	{
		if (it->type == Event::ET_KILL)
			addKill(*it);
		else if (it->type == Event::ET_DEATH)
			addDeath(*it);
	}
	uoBuff = gameState->ListShip2listUpdateObject();
	if (gameState->numPwrups() == 0)
	{
		int x = rand() % 2450 + 26;
		int y = rand() % 2450 + 26;
		gameState->addPwrup(x, y);
	}

	for (size_t i = 0; i < uoBuff.size(); ++i)
		commServer->sendUpdateToAll(uoBuff[i]);
}

void ServerEngine::sendScores()
{
	ServerMessage sm;
	ostringstream oss;
	for (size_t i = 0; i < playerList.size(); i++)
		oss << playerList[i] << "|";
	sm.SetMsgType(ServerMessage::MT_SCORES);
	sm.SetData(oss.str());
	commServer->sendServerMsgToAll(sm);
}

void ServerEngine::addDeath(Event event)
{
	ostringstream oss;
	oss << "* " << getPlayerName(event.killed) << " was killed by a wall *";
	ServerMessage m;
	m.SetData(oss.str());
	m.SetMsgType(ServerMessage::MT_CHAT);
	commServer->sendServerMsgToAll(m);

	oss.str("");
	oss << event.killed << "," << event.pos.x() << "," << event.pos.y();
	m.SetData(oss.str());
	m.SetClientID(event.killed);
	m.SetMsgType(ServerMessage::MT_DEATH);
	commServer->sendServerMsgToAll(m);

	ScoreBoard::Instance()->recordDeath(event.killed);

	for (size_t i = 0; i < playerList.size(); i++)
	{
		if (playerList[i].getId() == event.killed)
		{
			playerList[i].addDeath();
			break;
		}
	}
	sendScores();
}

void ServerEngine::addKill(Event event)
{
	ostringstream oss;
	oss << "* " << getPlayerName(event.killed) << " was killed by " << getPlayerName(event.killer) << " *";
	ServerMessage m;
	m.SetData(oss.str());
	m.SetClientID(event.killed);
	m.SetMsgType(ServerMessage::MT_CHAT);
	commServer->sendServerMsgToAll(m);

	oss.str("");
	oss << event.killed << "," << event.pos.x() << "," << event.pos.y();
	m.SetData(oss.str());
	m.SetMsgType(ServerMessage::MT_DEATH);
	commServer->sendServerMsgToAll(m);

	ScoreBoard::Instance()->recordKill(event.killed, event.killer);

	for (size_t i = 0; i < playerList.size(); i++)
	{
		if (playerList[i].getId() == event.killer)
			playerList[i].addKill();
		else if (playerList[i].getId() == event.killed)
			playerList[i].addDeath();
	}
	sendScores();
}

bool ServerEngine::isNameUsed(string name)
{
	for (size_t i = 0; i < playerList.size(); i++)
		if (playerList[i].getName() == name)
			return true;
	return false;
}

string ServerEngine::getPlayerName(int id)
{
	for (size_t i = 0; i < playerList.size(); i++)
		if (playerList[i].getId() == id)
			return playerList[i].getName();
	return "";
}

ServerEngine* ServerEngine::GetInstance()
{
    if (!instance)
        instance = new ServerEngine();

    return instance;
}

void ServerEngine::Shutdown(int code)
{
	if (instance->timer)
	{
		instance->timer->stop();
		delete instance->timer;
		instance->timer = 0;
	}

	if (instance->commServer)
	{
		instance->commServer->Shutdown();
		instance->commServer = 0;
	}

	if (instance->gameState)
	{
		delete instance->gameState;
		instance->gameState = 0;
	}

	exit(code);
}
