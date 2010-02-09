#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QTimer>

class BaseWindow : public QMainWindow
{
    private:
        QTimer timer;

    public:
        BaseWindow();

    private:
        /*
         * Gets called everytime keyboard input occurs
         */
        void keyPressed(int);

        /*
         * Used to update game information when time event fires.
         */
        void update();
};

#endif // BASEWINDOW_H
