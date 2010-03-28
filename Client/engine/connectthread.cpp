#include "connectthread.h"
#include "Comm/Commclient.h"
using namespace std;

ConnectThread::ConnectThread(string name, string ip, string port)
: name_(name), ip_(ip), port_(port)
{ }


void ConnectThread::run()
{
	int clientId;
	if ((clientId = CommClient::Instance()->connect(name_, ip_, port_)) < 0)
		emit errorConnect();
	else
		emit serverConnect(clientId);
}
