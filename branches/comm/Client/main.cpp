#include "main.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    CommClient *cc = CommClient::Instance();

    cc->connect("kara", "192.168.0.12");

    ClientAction a(2);
    a.setAccelerating();
    a.setTurningRight();

    cc->sendAction(a);



    // insert main gfx window initilization here, which extends from BaseWindow 
    
    //GameWindow mainWin = new GameWindow();
    BaseWindow mainWin;
    
    mainWin.setWindowTitle("Game Window");
    
    mainWin.show();
    return app.exec();
}

