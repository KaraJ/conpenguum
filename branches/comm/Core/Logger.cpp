#include "Logger.h"

using namespace::std;

void LogNQuit(char* errorMsg)
{
	fstream logFile;
	logFile.open("Server.log");
	logFile << errorMsg << endl;
	logFile.close();
	exit(1);
}

void LogNContinue(char* errorMsg)
{

}
