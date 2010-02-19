#include "main.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // insert CommClient initilization 
    //CommClient cc = new CommClient();
    

    //************
    //testing the server
    struct sockaddr_in serv;
    char * data = "hello world";
    char out[1024];

    UDPClient cli(argv[1]);
    cli.sendMessage(data, sizeof(data) +1);
    cli.recvMessage((void *)out);
    cout << out << endl;
    //end test code
    //****************


    // insert main gfx window initilization here, which extends from BaseWindow 
    
    //GameWindow mainWin = new GameWindow();
    BaseWindow mainWin;
    
    mainWin.setWindowTitle("Game Window");
    
    mainWin.show();
    return app.exec();
}

