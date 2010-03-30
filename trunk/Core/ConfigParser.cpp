/*----------------------------------------------------------------------------------------
SOURCE FILE:	ConfigParser.cpp

PROGRAM:

FUNCTIONS:		bool ConfigParser::Parse(const string &fileName, map<string, string> &values)

DATE: 			March 16, 2010

DESIGNER: 		Aaron & Steve

PROGRAMMER: 	Aaron & Steve

NOTES:
				This file contains the implementation for the ConfigParser class
----------------------------------------------------------------------------------------*/

#include "ConfigParser.h"

using std::map;
using std::string;
using std::ifstream;
using std::istringstream;
using std::pair;

/*----------------------------------------------------------------------------------------
FUNCTION: 	ConfigParser::Parse

DATE: 		March 16, 2010

DESIGNER: 	Aaron & Steve

PROGRAMMER: Aaron & Steve

INTERFACE:	bool ConfigParser::Parse(const string &fileName, map<string, string> &values)
				string fileName - Name of the config file to parse
				map<string, string> values - reference to a map of configuration values

RETURNS:	True on success, false if there was a problem with the file

NOTES:
			This function parses through the specified configuration file and inserts the
			config setting and value as a pair into the map of values.
-----------------------------------------------------------------------------------------*/
bool ConfigParser::Parse(const string &fileName, map<string, string> &values)
{
    ifstream configFile;
    istringstream iss;
    string line;

    configFile.open(fileName.c_str());

    if (!configFile.is_open())
        return false;

    while (getline(configFile, line))
    {
    	iss.str(line);
        string parameter, value, delim;

        if (iss >> parameter && iss >> delim && delim.compare("=") == 0 && iss >> value)
			values.insert(pair<string, string>(parameter, value));
    }
	return true;
}
