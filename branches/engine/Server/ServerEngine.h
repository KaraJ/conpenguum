class ServerEngine
{
	private:
		CommServer::CommServer* server;
		std::vector<int> ids;
	
	public:
		ServerEngine();
		void runServer();
}