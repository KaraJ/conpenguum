/*----------------------------------------------------------------------------------------------------------
 --  SOURCE FILE: Logger.cpp
 --
 --  PROGRAM: TuxSpace
 --
 --  METHODS:
 --		void Logger::LogNQuit(const char* errorMsg)
 --		void Logger::LogNContinue(const char* errorMsg)
 --
 --  PROGRAMMER: Steve
 --
 --  REVISIONS (date and description):
 --
 --  DATE: 2010-01-23
 --
 --  NOTES: Singleton - retrieve reference through CommServer::Instance()
 ----------------------------------------------------------------------------------------------------------*/
#include "Logger.h"

using std::fstream;
using std::ios;
using std::endl;

/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: Logger::LogNQuit
 --
 -- DATE: 2010-01-23
 --
 -- INTERFACE:
 --		const char* errorMsg:	Error Message to print before quitting.
 ----------------------------------------------------------------------------------------------------------*/
void Logger::LogNQuit(const char* errorMsg)
{
	LogNContinue(errorMsg);
	exit(1);
}


/*----------------------------------------------------------------------------------------------------------
 -- FUNCTION: Logger::LogNContinue
 --
 -- DATE: 2010-01-23
 --
 -- INTERFACE:
 --		const char* errorMsg:	Error message to print.
 ----------------------------------------------------------------------------------------------------------*/
void Logger::LogNContinue(const char* errorMsg)
{
	fstream logFile;
	time_t currTime;

	perror(errorMsg);

	logFile.open("Server.log", ios::app | ios::out);
	time(&currTime);
	logFile << ctime(&currTime) << ": " << errorMsg << endl;
	logFile.close();
}
