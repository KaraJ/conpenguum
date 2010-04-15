#ifndef CONFIGPARSER_H_
#define CONFIGPARSER_H_

#include <string>
#include <map>
#include <fstream>
#include <sstream>

class ConfigParser
{
public:
	ConfigParser() {}
	virtual ~ConfigParser() {}
	bool Parse(const std::string &fileName, std::map<std::string, std::string> &values);
};

#endif
