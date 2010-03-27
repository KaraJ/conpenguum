#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <qmessagebox.h>
#include <qwidget.h>

class Logger
{
public:
	static void LogNQuit(const char* errorMsg);
	static void LogNContinue(const char* errorMsg);
};

#endif
