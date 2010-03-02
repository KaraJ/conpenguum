#include "main.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    CommClient *cc = CommClient::Instance();

    cout << "connecting" << endl;
    cc->connect("kara", "192.168.0.12");
    cout << "sending" << endl;
    ClientAction a(0);
    a.setAccelerating();
    a.setTurningRight();
    a.setTurningLeft();

    cc->sendAction(a);
    cout << "waiting" << endl;
    while(1)
    {
    	if(cc->hasNextUpdate())
    		cc->nextUpdate().print();
    }



    // insert main gfx window initilization here, which extends from BaseWindow 
    
    //GameWindow mainWin = new GameWindow();
    BaseWindow mainWin;
    
    mainWin.setWindowTitle("Game Window");
    
    mainWin.show();
    return app.exec();
}

