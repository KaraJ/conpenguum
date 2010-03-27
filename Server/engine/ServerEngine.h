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

class ServerEngine : public QObject
{
	Q_OBJECT
private:
	CommServer::CommServer* commServer;
	Frame *gameState;
	QTimer *timer;

private slots:
	void timeout();

public:
	ServerEngine();
	~ServerEngine();
};
