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
 --		Feb 11, 2010 - Updated the class interface - Erick Ribeiro
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
    private:
        QTimer timer;

    public:
        BaseWindow();

    private:
        void keyPressEvent (QKeyEvent* event);
        void update();
};

#endif // BASEWINDOW_H
