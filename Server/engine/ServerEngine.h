#include <iostream>
#include <vector>
#include "../comm/commserver.h"
#include "../../Core/comm/globals.h"
#include "../../Core/comm/data/clientaction.h"
#include "../../Core/comm/data/servermessage.h"
#include "../../Core/comm/data/updateobject.h"

/*------------------------------------------------------------------------------
 --
 -- CLASS: BaseWindow
 --
 -- METHODS:
 --
 --		[Constructor] ServerEngine()
 --		void RunServer()
 --
 -- DESIGNER: Brad Paugh
 --
 -- PROGRAMMER: Engine Team
 --
 -- REVISIONS:	(Date, Description, Author)
 --
 -- NOTES:
 -- This class runs the server and holds all the IDs currently
 -- connected to the server.
 --
 -----------------------------------------------------------------------------*/

class ServerEngine
{
	private:
		CommServer::CommServer* server;
		std::vector<int> ids;
	
	public:
		ServerEngine();
		void RunServer();
};