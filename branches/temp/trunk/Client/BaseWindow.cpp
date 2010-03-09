#include "BaseWindow.h"

/*------------------------------------------------------------------------------
 --
 -- CONSTRUCTOR: BaseWindow::BaseWindow()
 --
 -- DESIGNER: Erick Ribeiro
 --
 -- PROGRAMMER: Erick Ribeiro
 --
 -- NOTES:
 -- This is the main constructor of the BaseWindow class. It initializes
 -- the QTimer object used for timing and instantiates/retrieves the instance of
 -- the CommClient class.
 --
 -----------------------------------------------------------------------------*/

BaseWindow::BaseWindow()
{

   Panel *panel = new Panel();
    panel->setFocus();
    panel->show();

	// @todo Get CommClient instance here.
	// @todo Set up a QTimer object to call update() 60 times/second.
}

void BaseWindow::keyPressEvent (QKeyEvent *event)
{
	// @todo Keyboard handling here.
}

void BaseWindow::update()
{
	// @todo Call render().
}
