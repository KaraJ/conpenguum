#include "main.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // insert CommClient initialization
    //CommClient cc = new CommClient();
    

    //************
    //testing the server
    ClientAction action;
    action.setAccelerating();
    action.setTurningLeft();

    CommClient * cli = CommClient::Instance();
    cli->connect("kara", "127.0.0.1");
    cli->sendAction(action);
    cout << "waiting" << endl;
    while(!cli->hasNextUpdate())
    {}
    	cout << "got object" << endl;
    	cli->nextUpdate().print();

    //end test code
    //****************


    // insert main gfx window initilization here, which extends from BaseWindow 
    
    //GameWindow mainWin = new GameWindow();
    BaseWindow mainWin;
    
    mainWin.setWindowTitle("Game Window");
    
    mainWin.show();
    return app.exec();
}

