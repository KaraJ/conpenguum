#include <QtCore/QCoreApplication>

#include <iostream>
#include "clientaction.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ClientAction ca(1, 1);
    ca.setAccelerating();
    ca.setFiring();
    cout << "Accelerating: " << ca.isAccelerating() << endl;
    cout << "Firing: " << ca.isFiring() << endl;
    ca.clear();
    cout << "CLEAR" << endl;
    cout << "Accelerating: " << ca.isAccelerating() << endl;
    ca.setFiring();
    cout << "Firing: " << ca.isFiring() << endl;

    return a.exec();
}
