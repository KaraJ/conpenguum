#include "main.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QResource::registerResource("GUI/menuitems.rcc");

    // insert main gfx window initilization here, which extends from BaseWindow 
    
    //GameWindow mainWin = new GameWindow();
    BaseWindow mainWin;
    
    mainWin.setWindowTitle("Game Window");
    
    mainWin.show();
    return app.exec();
}

