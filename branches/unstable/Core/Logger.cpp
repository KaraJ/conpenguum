#include "Logger.h"

using namespace::std;

void Logger::LogNQuit(const char* errorMsg)
{
	fstream logFile;
	time_t currTime;

	logFile.open("Server.log", ios::app | ios::out);
	time(&currTime);
	logFile << ctime(&currTime) << ": " << errorMsg << endl;
	logFile.close();
	exit(1);
}

void Logger::LogNContinue(const char* errorMsg)
{
	fstream logFile;
	time_t currTime;

	logFile.open("Server.log", ios::app | ios::out);
	time(&currTime);
	logFile << ctime(&currTime) << ": " << errorMsg << endl;
	logFile.close();
}
