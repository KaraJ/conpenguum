#include "main.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(menuitems);

    Panel *panel = new Panel();
    panel->setFocus();
    panel->show();

    return app.exec();
}
