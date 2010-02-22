#include "BaseWindow.h"
#include "renderer.h"
#include "commclient.h"

/*------------------------------------------------------------------------------
 --
 -- CONSTRUCTOR: BaseWindow::BaseWindow()
 --
 -- DESIGNER: Erick Ribeiro
 --
 -- PROGRAMMER: Erick Ribeiro
 --
 -- REVISIONS:
 --
 --		Feb 18, 2010 - Erick Ribeiro
 --		Set up a QTimer object to call timerEvent() every interval.
 --
 -- NOTES:
 -- This is the main constructor of the BaseWindow class. It initializes
 -- the QTimer object used for timing.
 --
 -----------------------------------------------------------------------------*/
BaseWindow::BaseWindow() : timer(this)
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
}

/*------------------------------------------------------------------------------
 --
 -- METHOD: BaseWindow::keyPressEvent()
 --
 -- DESIGNER: Erick Ribeiro
 --
 -- PROGRAMMER:
 --
 -- REVISIONS:
 --
 -- NOTES:
 -- This method handles keyboard input. It's responsibility is to translate key
 -- presses to game actions, and send these actions to the server using the
 -- CommClient object.
 --
 -----------------------------------------------------------------------------*/
void BaseWindow::keyPressEvent (QKeyEvent * event)
{
	// @todo Keyboard handling here.
}

/*------------------------------------------------------------------------------
 --
 -- METHOD: BaseWindow::timerEvent()
 --
 -- DESIGNER: Erick Ribeiro
 --
 -- PROGRAMMER:
 --
 -- REVISIONS:
 --
 -- NOTES:
 -- This method is called by a QTimer object every frame. It's responsibility is
 -- to determine if the game scene needs to be rendered, and if so, it calls
 -- render() which is a virtual method implemented by a subclass.
 --
 -----------------------------------------------------------------------------*/
void BaseWindow::timerEvent()
{
	Renderer render(this);
	render.Render();
}
