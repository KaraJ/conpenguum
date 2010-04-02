#include "connectthread.h"
#include "Comm/Commclient.h"
using namespace std;

ConnectThread::ConnectThread(string name, string ip, string port)
: name_(name), ip_(ip), port_(port)
{ }


void ConnectThread::run()
{
	int clientId;
	switch (clientId = CommClient::Instance()->connect(name_, ip_, port_))
	{
	case -1: emit errorConnect(); break;
	case -2:
		CommClient::Instance()->disconnect();
		emit nameInUse();
		break;
	default: emit serverConnect(clientId); break;
	}
}
