#include "BaseWindow.h"

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
 -- the QTimer object used for timing and instantiates/retrieves the instance of
 -- the CommClient class.
 --
 -----------------------------------------------------------------------------*/

BaseWindow::BaseWindow() : timer(this)
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
	timer.start(17); // Just over 60 times/second.
}

void BaseWindow::keyPressEvent (QKeyEvent * event)
{
	// @todo Keyboard handling here.
}

void BaseWindow::timerEvent()
{
	// @todo Call render().
}
