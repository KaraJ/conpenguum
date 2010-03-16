ServerEngine::ServerEngine()
{
	server = CommServer::Instance();
	server -> init();
}

void ServerEngine::RunServer()
{
	while(1)
	{
		if (server -> hasNextClientAction())
		{
			ClientAction ca = server->nextClientAction();
			UpdateObject uo(ca.getClientID());
			//gameplay updates updateObject
			server -> sendUpdate(uo, ids);
		}
	}
}
