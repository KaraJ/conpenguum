//#include "MainWindow.h"
#include "BaseWindow.h" //remove this
int main(int argc, char * argv[]){
    QApplication app(argc, argv);

    /* insert CommClient initilization */
    //CommClient cc = new CommClient();

    /* insert main gfx window initilization here, which extends from BaseWindow */
    //GameWindow mainWin = new GameWindow();
    BaseWindow mainWin;

    mainWin.setWindowTitle("Game Window");

    mainWin.show();
    return app.exec();
}


