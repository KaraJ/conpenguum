#include "TCPServer.h"

using namespace std;

int TCPServer::clients_[32];
sem_t *TCPServer::semSM_;
queue<ServerMessage> *TCPServer::msgBuff_;
queue<in_addr> *TCPServer::clientVec_;

TCPServer::TCPServer()
{
	bzero(clients_, 32 * sizeof(int));
}

void TCPServer::Init(const string port)
{
	istringstream iss(port);
	int tmp = 1;

	listenSocket_ = SocketWrapper::Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	setsockopt(listenSocket_, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp));

	sockaddr_in sa_ =
	{ 0 };
	iss >> tmp;
	sa_.sin_family = AF_INET;
	sa_.sin_addr.s_addr = htonl(INADDR_ANY);
	sa_.sin_port = htons(tmp);

	SocketWrapper::Bind(listenSocket_, &sa_, sizeof(sa_));
}

void TCPServer::StartReadThread(queue<ServerMessage> *serverMsgs, queue<in_addr> *clients, sem_t *semSM)
{
	TCPServer::msgBuff_ = serverMsgs;
	TCPServer::semSM_ = semSM;
	TCPServer::clientVec_ = clients;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	if (pthread_create(&rThread_, &attr, TCPServer::ReadThread, &listenSocket_))
		Logger::LogNQuit("TCPServer: Unable to start listen thread.");
}

void* TCPServer::ReadThread(void* vptr)
{
	int sock = *(int*) vptr;
	sockaddr_in sa;
	int client, ready, maxClient = sock;
	uint size;
	fd_set currSet, clientSet;
	ServerMessage msgBuff;

	SocketWrapper::Listen(sock, 5);

	FD_ZERO(&clientSet);
	FD_SET(sock, &clientSet);

	while (true)
	{
		currSet = clientSet;
		ready = select(maxClient + 1, &currSet, NULL, NULL, NULL);

		if (FD_ISSET(sock, &currSet))
		{
			client = SocketWrapper::Accept(sock, &sa, &size);
			clientVec_->push(sa.sin_addr);
			for (int i = 0; i < 32; ++i)
			{
				if (clients_[i] == 0)
				{
					clients_[i] = client;
					if (i > maxClient)
						maxClient = i;
					break;
				}
			}
			FD_SET(client, &clientSet);

			if (--ready == 0)
				continue;
		}
		for (int i = 0; i < 32; ++i)
		{
			if ((client = clients_[i]) == 0)
				continue;
			if (FD_ISSET(client, &currSet))
			{
				TCPConnection::ReadMessage(client, msgBuff);
				sem_wait(semSM_);
				msgBuff_->push(msgBuff);
				sem_post(semSM_);
			}
		}
	}

	return 0;
}
