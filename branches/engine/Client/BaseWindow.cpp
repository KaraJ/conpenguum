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
BaseWindow::BaseWindow() : timer(this), frameRate(DEFAULT_FRAME_RATE)
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
 --		Feb 22, 2010 - Erick Ribeiro
 --		Changed the way render() was being called. We don't need to create a
 --		renderer object. We just need to call render(), which will be
 --		implemented by the Graphics Team in a subclass of BaseWindow.
 --
 -- NOTES:
 -- This method is called by a QTimer object for every frame. It's
 -- responsibility is to determine if the game scene needs to be rendered, and
 -- if so, it calls render().
 --
 -----------------------------------------------------------------------------*/
void BaseWindow::timerEvent()
{
	render();
}

/*------------------------------------------------------------------------------
 --
 -- METHOD: BaseWindow::startRendering()
 --
 -- DESIGNER: Erick Ribeiro
 --
 -- PROGRAMMER: Erick Ribeiro
 --
 -- REVISIONS:
 --
 -- NOTES:
 -- Call this method to start the timer mechanism resposible for calling
 -- render() for every frame.
 --
 -----------------------------------------------------------------------------*/
void BaseWindow::startRendering ()
{
	timer.start(1000/frameRate);
}

/*------------------------------------------------------------------------------
 --
 -- METHOD: BaseWindow::stopRendering()
 --
 -- DESIGNER: Erick Ribeiro
 --
 -- PROGRAMMER: Erick Ribeiro
 --
 -- REVISIONS:
 --
 -- NOTES:
 -- Call this method to stop the timer mechanism resposible for calling
 -- render() for every frame.
 --
 -----------------------------------------------------------------------------*/
void BaseWindow::stopRendering ()
{
	timer.stop();
}

/*------------------------------------------------------------------------------
 --
 -- METHOD: BaseWindow::setFrameRate(int rate)
 --
 -- DESIGNER: Erick Ribeiro
 --
 -- PROGRAMMER: Erick Ribeiro
 --
 -- REVISIONS:
 --
 -- PARAMETERS:
 --		int rate - The amount of frames per second.
 --
 -- NOTES:
 -- This method updates the frame rate used for calling render().
 --
 -----------------------------------------------------------------------------*/
void BaseWindow::setFrameRate (int rate)
{
	frameRate = rate;
	timer.setInterval(1000/rate);
}

/*------------------------------------------------------------------------------
 --
 -- METHOD: BaseWindow::render()
 --
 -- DESIGNER: Erick Ribeiro
 --
 -- PROGRAMMER: Erick Ribeiro
 --
 -- REVISIONS:
 --
 -- NOTES:
 -- This method is just an empty virtual method. It must be overriden by
 -- subclasses to implement the actual rendering functionality. This method is
 -- called automatically for every frame.
 --
 -----------------------------------------------------------------------------*/
void BaseWindow::render ()
{
}