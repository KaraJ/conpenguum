#include "BaseWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    BaseWindow mainWin;
    
    mainWin.setWindowTitle("Game Window");
    mainWin.show();

	QTimer::singleShot(1000, &mainWin, SLOT(myTimeEvent()));

    return app.exec();
}

