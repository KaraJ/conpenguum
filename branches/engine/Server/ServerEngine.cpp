#include "ServerEngine.h"

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
	server = CommServer::Instance();
	server -> init();
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
			if (sm.GetMsgType() == 1)
			{
				ids.push_back(sm.GetClientID());
				/*check if we need to send the init message
					or if its sent automatically on connect*/
			}
			//user has logged out, remove client id from vector
			if (sm.GetMsgType() == 2)
			{
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
			if (sm.GetMsgType() == 6)
			{
				server->sendServerMsg(sm, ids);
			}
		}
		if (server -> hasNextClientAction())
		{
			ClientAction ca = server->nextClientAction();
			UpdateObject uo(ca.getClientID());
			//gameplay updates updateObject here
			server -> sendUpdate(uo, ids);
		}
	}
}
