#include <iostream>
#include "ServerEngine.h"

using namespace std;

int main()
{
	cout << "Conpenguum server starting..." << endl;
	ServerEngine* se = new ServerEngine();
	se->RunServer();
}