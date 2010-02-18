#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>

/*------------------------------------------------------------------------------
 --
 -- CLASS: BaseWindow
 --
 -- METHODS:
 --
 --		[Constructor] BaseWindow (void)
 --		void keyPressEvent (QKeyEvent * event)
 --		void update ()
 --
 -- DESIGNER: Erick Ribeiro
 --
 -- PROGRAMMER: Engine Team
 --
 -- REVISIONS:	(Date, Description, Author)
 --
 --		Feb 11, 2010 - Erick Ribeiro
 --		Updated the class interface
 --
 --		Feb 18, 2010 - Erick Ribeiro
 --		Renamed method update() to timerEvent() because QWidget (super class)
 --		already has an update() method which is used for a different purpose.
 --
 --		Feb 18, 2010 - Erick Ribeiro
 --		Added the Q_OBJECT macro so we can define our own signals and slots,
 --		such as the timerEvent() slot.
 --
 -- NOTES:
 -- This class extends the QTMainWindow class, adding keyboard input handling
 -- and timing logic.
 --
 -- The Graphics Team should extend this class and override the render() method,
 -- which gets called every frame, in order to implement the drawing logic.
 --
 -----------------------------------------------------------------------------*/

class BaseWindow : public QMainWindow
{
	// This macro must be present to
	// activate signals/slots.
	// Do not change.
	Q_OBJECT

    private:
        QTimer timer;

    public:
        BaseWindow();

    private:
        void keyPressEvent (QKeyEvent * event);

	public slots:
        void timerEvent();
};

#endif // BASEWINDOW_H
