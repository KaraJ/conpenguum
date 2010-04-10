#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include <mysql++.h>
#include <map>
#include <string>

#include "../Core/Player.h"
#include "../Core/ConfigParser.h"
#include "../Core/Logger.h"

class ScoreBoard {
public:
	static ScoreBoard* Instance();
	void addPlayer(int id, std::string name);
	void removePlayer(int id);
	void recordKill(int deadPlayer, int killedBy);
	void recordDeath(int deadPlayer);
	virtual ~ScoreBoard(){}
private:
	ScoreBoard();
	std::map<int, Player> players;
	mysqlpp::Connection conn;
	bool db_connected;
	void execQuery(std::string query);
	mysqlpp::StoreQueryResult storeQuery(std::string query);
};

#endif
