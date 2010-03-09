#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <stdlib.h>
#include <time.h>

class Logger
{
public:
	static void LogNQuit(const char* errorMsg);
	static void LogNContinue(const char* errorMsg);
};

#endif /* LOGGER_H_ */
