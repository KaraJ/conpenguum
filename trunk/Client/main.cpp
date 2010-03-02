#include "main.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // insert main gfx window initilization here, which extends from BaseWindow 
    
    //GameWindow mainWin = new GameWindow();
    BaseWindow mainWin;
    
    mainWin.setWindowTitle("Game Window");
    
    mainWin.show();
    return app.exec();
}

