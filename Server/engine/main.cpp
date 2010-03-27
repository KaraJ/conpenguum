#include "ServerEngine.h"
#include <QApplication>

using namespace std;
ServerEngine* se;
void Shutdown(int code);
int main(int argc, char** argv)
{
	se = NULL;
	signal(SIGINT, Shutdown);
    QApplication app(argc, argv);
	se = new ServerEngine();
	return app.exec();
}
void Shutdown(int code)
{
	delete se;
	exit(code);
}
