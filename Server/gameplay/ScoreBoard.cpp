#include "ScoreBoard.h"

using std::string;
using std::map;
using std::exception;

ScoreBoard* ScoreBoard::Instance()
{
	static ScoreBoard* instance = 0;
	if(instance == 0)
		instance = new ScoreBoard();
	return instance;
}

ScoreBoard::ScoreBoard()
{
	ConfigParser cp;
	map<string, string> params;
	if(!cp.Parse("server.conf", params))
	{
		Logger::LogNContinue("Invalid Parser");
	}
	else
	{
		try
		{
			if(conn.connect(params["database_name"].c_str(), params["database_host"].c_str(), params["database_user"].c_str(), params["database_pass"].c_str()))
			{
				execQuery("DELETE FROM currentGame");
				db_connected = true;
			}
			else
			{
				Logger::LogNContinue("Could not connect to database continuing as normal.");
				db_connected = false;
			}
		}
		catch (exception e)
		{
			Logger::LogNContinue(e.what());
		}
	}
}
void ScoreBoard::addPlayer(int id, string name)
{
	players[id] = Player(id, name);
	if(db_connected)
	{
		execQuery("INSERT INTO currentGame (username) VALUES ('" + players[id].getName() + "')");
	}
}

void ScoreBoard::removePlayer(int id)
{
	if(db_connected)
	{
		if(storeQuery("SELECT username FROM pastGames WHERE username = '" + players[id].getName() + "'").num_rows() == 0)
		{
			execQuery("INSERT INTO pastGames (SELECT * FROM currentGame WHERE username='" + players[id].getName() + "')");
		}
		else
		{
			execQuery("UPDATE pastGames SET kills=kills+" + players[id].getKillsString() + ", deaths=deaths+" + players[id].getDeathsString() + " WHERE username = '" + players[id].getName() + "'");
		}
		execQuery("DELETE FROM currentGame WHERE username = '" + players[id].getName() +"'");
	}
	players.erase(id);
}

void ScoreBoard::recordKill(int deadPlayer, int killedBy)
{
	players[deadPlayer].addDeath();
	players[killedBy].addKill();
	if(db_connected)
	{
		execQuery("UPDATE currentGame SET kills=" + players[deadPlayer].getKillsString() + ", deaths=" + players[deadPlayer].getDeathsString() + " WHERE username = '" + players[deadPlayer].getName() + "'");
		execQuery("UPDATE currentGame SET kills=" + players[killedBy].getKillsString() + ", deaths=" + players[killedBy].getDeathsString() + " WHERE username = '" + players[killedBy].getName() + "'");
	}
}

void ScoreBoard::execQuery(string query)
{
	try
	{
		conn.query(query.c_str()).execute();
	}
	catch (exception e)
	{
		Logger::LogNContinue(e.what());
	}
}

mysqlpp::StoreQueryResult ScoreBoard::storeQuery(string query)
{
	mysqlpp::StoreQueryResult res;
	try
	{
		res = conn.query(query.c_str()).store();
	}
	catch (exception e)
	{
		Logger::LogNContinue(e.what());
	}
	return res;
}
