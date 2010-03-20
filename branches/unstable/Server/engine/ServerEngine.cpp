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
		server = CommServer::Instance();
		server -> init(params["tcp_port"]);
	}
	else
		cerr << "Invalid configuration file." << endl;
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
void ServerEngine::RunServer()
{
	while(1)
	{
		/*todo: this is currently polling, very inefficient,
			consult with the comm team to figure out
			how this should be implemented.*/
		if (server -> hasNextServerMessage())
		{
			ServerMessage sm = server->nextServerMessage();
			
			//user has logged in, add client id to ID vector
			if (sm.GetMsgType() == ServerMessage::MT_LOGIN)
			{
				cout << "client logged in" << endl;
				ids.push_back(sm.GetClientID());
				ServerMessage init;
				init.SetMsgType(ServerMessage::MT_INIT);
				init.SetClientID(sm.GetClientID());
				init.SetData("");
				server->sendServerMsg(init);
				/*check if we need to send the init message
					or if its sent automatically on connect*/
			}
			//user has logged out, remove client id from vector
			if (sm.GetMsgType() == ServerMessage::MT_LOGOUT)
			{
				cout << "client logged out" << endl;
				size_t id = sm.GetClientID();
				vector<int>::iterator it;
				//iterate over all vectors and find the ID to delete
				for (it = ids.begin(); it != ids.end(); it++)
				{
					if (id == *it)
					{
						ids.erase(it);
					}
				}
			}
			//receive chat message.. send to all clients
			if (sm.GetMsgType() == ServerMessage::MT_CHAT)
			{
				cout << "Received chat msg: " << sm.GetData() << endl;
				server->sendServerMsg(sm, ids);
			}
		}
		if (server -> hasNextClientAction())
		{
			ClientAction ca = server->nextClientAction();
			cout << "Received client action" << endl;
			ca.print();
			cout.flush();
			//UpdateObject uo(ca.getClientID());
			//gameplay updates updateObject here
			//server -> sendUpdate(uo, ids);
		}
	}
}
