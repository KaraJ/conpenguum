#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <map>
#include <string>
#include <iostream>
#include "GameObject.h"
#include "../Animation/Animation.h"
#include "../Comm/Commclient.h"
#include "../../Core/comm/data/clientaction.h"
#include "../../Core/comm/data/servermessage.h"
#include "../Renderer/Renderer.h"

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
		std::vector<GameObject> gameState;
		std::map<int, Animation> animationMap;
		bool chatting;
		std::string chatString;
		CommClient::CommClient* theClient;
		size_t clientID;
		Renderer* ren;
		ClientAction* clientAction;

    public:
		BaseWindow ();
		void startRendering ();
		void stopRendering ();
		void setFrameRate (int rate);
		void keyPressEvent (QKeyEvent * event);
		void keyReleaseEvent (QKeyEvent * event);
		virtual void render ();
		std::string getChatString();
		void Start();
		void getServerMessage();

	public slots:
		void timerEvent();

	private:
		void updateGameState();
		int handleChat(int key);
		void toggleChat();
};

#endif // BASEWINDOW_H
