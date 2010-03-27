#include <QtCore/QCoreApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if (argc < 3) {
        std::cerr << "Usage: MapTranslator <types.xml> <map.tmx>" << std::endl;
    }

    std::cout << argc << std::endl;

    //return a.exec();
}
