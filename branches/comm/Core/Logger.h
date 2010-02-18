#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <stdlib.h>

class Logger
{
public:
	static void LogNQuit(char* errorMsg);
	static void LogNContinue(char* errorMsg);
};

#endif /* LOGGER_H_ */
