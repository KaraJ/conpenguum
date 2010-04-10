/*------------------------------------------------------------------------------
 --
 -- CLASS: BaseWindow
 --
 -- METHODS:
 --
 --		[Constructor] ServerEngine()
 --		void RunServer()
 --
 -- DESIGNER: Brad Paugh
 --
 -- PROGRAMMER: Engine Team
 --
 -- REVISIONS:	(Date, Description, Author)
 --
 -- NOTES:
 -- This class runs the server and holds all the IDs currently
 -- connected to the server.
 --
 -----------------------------------------------------------------------------*/

//System Include
#include <QObject>
#include <QTimer>
#include <vector>
#include <signal.h>

//User Include
#include "../gameplay/Frame.h"
#include "../comm/commserver.h"
#include "../../Core/comm/globals.h"
#include "../../Core/Player.h"
#include "../gameplay/ScoreBoard.h"

class ServerEngine : public QObject
{
	Q_OBJECT

public:
	static ServerEngine* GetInstance();
	bool Start();

private:
	ServerEngine();
	static void Shutdown(int code);
	bool isNameUsed(std::string name);
	std::string getPlayerName(int id);
	void addDeath(int killed);
	void addKill(int killed, int killer);
	void sendScores();

	QTimer *timer;
	CommServer::CommServer* commServer;
	Frame *gameState;
	static ServerEngine *instance;
	std::vector<Player> playerList;

private slots:
	void timeout();
};
