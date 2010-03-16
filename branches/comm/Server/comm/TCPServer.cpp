#include "TCPServer.h"

//TODO: delete this
#include "commserver.h"

using namespace std;

int TCPServer::clientSockets_[MAX_CLIENTS];
sem_t *TCPServer::semSM_;
queue<ServerMessage> *TCPServer::msgBuff_;
map<int,in_addr> *TCPServer::clientAddressMap_;

TCPServer::TCPServer()
{
	bzero(clientSockets_, MAX_CLIENTS * sizeof(int));
}

void TCPServer::Init(const string port)
{
	istringstream iss(port);
	int tmp = 1;

	listenSocket_ = SocketWrapper::Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	setsockopt(listenSocket_, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp));

	sockaddr_in sa_ = { 0 };
	iss >> tmp;
	sa_.sin_family = AF_INET;
	sa_.sin_addr.s_addr = htonl(INADDR_ANY);
	sa_.sin_port = htons(tmp);

	SocketWrapper::Bind(listenSocket_, &sa_, sizeof(sa_));
}

void TCPServer::StartReadThread(queue<ServerMessage> *serverMsgs, map<int,in_addr> *clients, sem_t *semSM)
{
	TCPServer::msgBuff_ = serverMsgs;
	TCPServer::semSM_ = semSM;
	TCPServer::clientAddressMap_ = clients;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	if (pthread_create(&rThread_, &attr, TCPServer::ReadThread, &listenSocket_))
		Logger::LogNQuit("TCPServer: Unable to start listen thread.");
}

void* TCPServer::ReadThread(void* vptr)
{
	int listenSocket = *(int*) vptr;
	sockaddr_in sa;
	int clientSocket, ready, maxClientSocket = listenSocket;
	uint size;
	fd_set currSet, allSet;
	ServerMessage msgBuff;
	bool isFull;

	FD_ZERO(&allSet);
	FD_SET(listenSocket, &allSet);
	SocketWrapper::Listen(listenSocket, 5);

	while (true)
	{
		currSet = allSet;

		ready = select(maxClientSocket + 1, &currSet, NULL, NULL, NULL);

		if (FD_ISSET(listenSocket, &currSet))
		{
			size = sizeof(sa);
			clientSocket = SocketWrapper::Accept(listenSocket, &sa, &size);
			isFull = true;
			for (int i = 0; i < MAX_CLIENTS; ++i)
			{
				if (clientSockets_[i] == 0)
				{
					clientAddressMap_->insert(pair<int, in_addr>(i,sa.sin_addr));
					clientSockets_[i] = clientSocket;
					if (clientSocket > maxClientSocket)
						maxClientSocket = clientSocket;
					FD_SET(clientSocket, &allSet);
					isFull = false;
					break;
				}
			}
			if (isFull)
			{
				ServerMessage m;
				m.SetMsgType(ServerMessage::MT_FULL);
				m.SetData("");
				TCPConnection::WriteMessage(clientSocket, m);
			}

			if (--ready == 0)
				continue;
		}
		for (int i = 0; i < MAX_CLIENTS; ++i)
		{
			if ((clientSocket = clientSockets_[i]) == 0)
				continue;

			if (FD_ISSET(clientSocket, &currSet))
			{
				if (TCPConnection::ReadMessage(clientSocket, msgBuff))
				{
					switch (msgBuff.GetMsgType())
					{
					case ServerMessage::MT_LOGIN: //If login msg, client doesnt know own id yet - add it
						msgBuff.SetClientID(i);
						//TODO: Delete this
						msgBuff.SetMsgType(ServerMessage::MT_INIT);
						CommServer::Instance()->sendServerMsg(msgBuff);

						break;
					}
					sem_wait(semSM_);
					msgBuff_->push(msgBuff);
					sem_post(semSM_);
				}
				else
				{
					msgBuff.SetClientID(i);
					msgBuff.SetData("");
					msgBuff.SetMsgType(ServerMessage::MT_LOGOUT);
					sem_wait(semSM_);
					msgBuff_->push(msgBuff);
					sem_post(semSM_);
					FD_CLR(clientSocket, &allSet);
					clientSockets_[i] = 0;
					if (clientSockets_[i] == maxClientSocket)
						maxClientSocket--;
					clientAddressMap_->erase(i);
					close(clientSocket);
				}
			}

			if (--ready == 0)
				continue;
		}
	}

	return 0;
}

void TCPServer::SendMessage(ServerMessage msg)
{
	TCPConnection::WriteMessage(clientSockets_[msg.GetClientID()], msg);
}

void TCPServer::SendMessageToAll(ServerMessage msg)
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		msg.SetClientID(clientSockets_[i]);
		TCPConnection::WriteMessage(msg.GetClientID(), msg);
	}
}
