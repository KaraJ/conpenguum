#include "TCPServer.h"


using std::string;
using std::queue;
using std::map;
using std::istringstream;
using std::pair;

int TCPServer::clientSockets_[MAX_CLIENTS];
int TCPServer::maxClientSocket_ = 0;
fd_set TCPServer::allSet_;
sem_t *TCPServer::semSM_;
queue<ServerMessage> *TCPServer::msgBuff_;
map<int,in_addr> *TCPServer::clientAddressMap_;
bool TCPServer::activeClients[MAX_CLIENTS];

TCPServer::TCPServer()
{
	bzero(clientSockets_, MAX_CLIENTS * sizeof(int));
	memset(activeClients, false, sizeof(bool) * MAX_CLIENTS);
}

void TCPServer::Init(const string port)
{
	istringstream iss(port);
	int tmp = 1;

	listenSocket_ = SocketWrapper::Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	setsockopt(listenSocket_, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp));

	sockaddr_in sa_;
	bzero(&sa_, sizeof(sockaddr_in));
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
	int clientSocket, ready;
	uint size;
	fd_set currSet;
	ServerMessage msgBuff;
	bool isFull;

	FD_ZERO(&allSet_);
	FD_SET(listenSocket, &allSet_);
	SocketWrapper::Listen(listenSocket, 5);
	maxClientSocket_ = listenSocket;

	for (int i = 0; i < MAX_CLIENTS; i++)
		clientSockets_[i] = 0;

	while (true)
	{
		currSet = allSet_;

		ready = select(maxClientSocket_ + 1, &currSet, NULL, NULL, NULL);

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
					if (clientSocket > maxClientSocket_)
						maxClientSocket_ = clientSocket;
					FD_SET(clientSocket, &allSet_);
					isFull = false;
					break;
				}
			}
			if (isFull)
			{
				ServerMessage m;
				m.SetData("");
				m.SetMsgType(ServerMessage::MT_FULL);
				TCPConnection::WriteMessage(clientSocket, m);
			}

			if (--ready == 0)
				continue;
		}
		for (int clientID = 0; clientID < MAX_CLIENTS; ++clientID)
		{
			if ((clientSocket = clientSockets_[clientID]) == 0)
				continue;

			if (FD_ISSET(clientSocket, &currSet))
			{
				if (TCPConnection::ReadMessage(clientSocket, msgBuff))
				{
					switch (msgBuff.GetMsgType())
					{
					case ServerMessage::MT_LOGIN: //If login msg, client doesnt know own id yet - add it
						msgBuff.SetClientID(clientID);
						break;
					}
					sem_wait(semSM_);
					msgBuff_->push(msgBuff);
					sem_post(semSM_);
				}
				else
				{
					SendLogoutMessage(clientID);
					ClientDC(clientID);
				}
			}
			if (--ready == 0)
				continue;
		}
	}
	return 0;
}

void TCPServer::SendLogoutMessage(int clientId)
{
	std::cout << "Logged Out " << clientId << std::endl;
	if (isClientActive(clientId))
	{
		ServerMessage logoutMsg;
		logoutMsg.SetClientID(clientId);
		logoutMsg.SetData("");
		logoutMsg.SetMsgType(ServerMessage::MT_LOGOUT);
		sem_wait(semSM_);
		msgBuff_->push(logoutMsg);
		sem_post(semSM_);
	}
}

void TCPServer::ClientDC(int clientId)
{
	std::cout << "Disconnected " << clientId << std::endl;
	int clientSocket = clientSockets_[clientId];
	FD_CLR(clientSocket, &allSet_);
	clientSockets_[clientId] = 0;
	if (clientSocket == maxClientSocket_)
		maxClientSocket_--;
	clientAddressMap_->erase(clientId);
	close(clientSocket);
}

void TCPServer::SendMessage(ServerMessage msg)
{
	if (!TCPConnection::WriteMessage(clientSockets_[msg.GetClientID()], msg))
	{
		SendLogoutMessage(msg.GetClientID());
		ClientDC(msg.GetClientID());
	}
}

void TCPServer::SendMessageToAll(ServerMessage msg)
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (clientSockets_[i])
		{
			msg.SetClientID(i);
			if (!TCPConnection::WriteMessage(clientSockets_[i], msg))
			{
				SendLogoutMessage(i);
				ClientDC(i);
			}
		}
	}
}
