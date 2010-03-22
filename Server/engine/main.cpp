#include "ServerEngine.h"
#include <QApplication>

using namespace std;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
	ServerEngine* se = new ServerEngine();
	return app.exec();
}
