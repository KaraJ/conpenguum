#ifndef BASEWINDOW_HureName
#define BASEWINDOW_H

//System Includes
#include <QtGui>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTextStream>
#include <QTimer>
#include <iostream>
#include <string>
#include <queue>
#include <sstream>

//User Includes
#include "GameObject.h"
#include "../Animation/Animation.h"
#include "../Comm/Commclient.h"
#include "../../Core/comm/data/clientaction.h"
#include "../../Core/comm/data/servermessage.h"
#include "../../Core/Player.h"
#include "../Renderer/Renderer.h"
#include "Map.h"

// Default frame rate is 30 frames/second.
#define DEFAULT_FRAME_RATE 30

/*------------------------------------------------------------------------------
 --
 -- CLASS: BaseWindow
 --
 -- METHODS:
 --
 --		[Constructor] BaseWindow (void)
 --		void keyPressEvent (QKeyEvent * event)
 --		void timerEvent ()
 --		void startRendering()
 --		void stopRendering()
 --		void setFrameRate(int rate)
 --		virtual void render ()
 --
 -- DESIGNER: Erick Ribeiro
 --
 -- PROGRAMMER: Engine Team
 --
 -- REVISIONS:	(Date, Description, Author)
 --
 --		Feb 18, 2010 - Erick Ribeiro
 --		Renamed method update() to timerEvent() because QWidget (super class)
 --		already has an update() method which is used for a different purpose.
 --
 --		Feb 18, 2010 - Erick Ribeiro
 --		Added the Q_OBJECT macro so we can define our own signals and slots,
 --		such as the timerEvent() slot.
 --
 --		Feb 22, 2010 - Erick Ribeiro
 --		Added the virtual method render(), which should be implemented by
 --		any subclasses. We use a timer mechanism to automatically call render()
 --		for every frame.
 --
 --		Feb 22, 2010 - Erick Ribeiro
 --		Added methods startRendering(), stopRendering() and setFrameRate() to
 --		offer more control over when and how often render() should be called.
 --
 --		Mar 23, 2010 Daraius Dastoor
 --		Removed std:: BaseWindow is now using namespace std and changed CTOR
 --
 -- NOTES:
 -- This class extends the QTMainWindow class, adding keyboard input handling
 -- and frame rate logic.
 --
 -- The Graphics Team should extend this class, override the render() method and
 -- call startRendering() so that render() will be called for every frame.
 --
 -----------------------------------------------------------------------------*/

class BaseWindow : public QMainWindow
{
	// This macro must be present to
	// activate signals/slots.
	// Do not change.
	Q_OBJECT

    private:
		int frameRate;
		QTimer timer;
		std::map<int, GameObject> gameState;
		std::map<int, Animation> animationMap;
		std::queue<int> freeExhaustIds;
		std::queue<int> freeExplosionIds;
		bool chatting;
		int chatIndex;
		bool shift;
		std::string chatString;
		QString localChat;
		std::deque<QString> chatQueue;
		std::vector<QString> vChatString;
		CommClient::CommClient* theClient;
		QPoint scrnCenter;
		Renderer* ren;
		ClientAction* clientAction;
		std::vector<Player> playerList;
        Map *m;
        int bankIndex[MAX_CLIENTS];

    public:
		BaseWindow ();
		void startRendering ();
		void stopRendering ();
		void setFrameRate (int rate);
		void keyPressEvent (QKeyEvent * event);
		void keyReleaseEvent (QKeyEvent * event);
		std::string getChatString();
		void Start(int clientId);
		void getServerMessage();

	public slots:
		void timerEvent();

	private:
		void updateGameState();
		void clearTransientObjects();
		int handleChat(int key);
		void toggleChat();
		QString getName(int);
		void createObject(UpdateObject &updateObj, int objId);
};

#endif // BASEWINDOW_H
