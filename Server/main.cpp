#include <iostream>
#include <QPoint>
#include "physics.h"
#include "frame.h"
#include "ship.h"

using namespace std;
int main() {
    Frame frame;
    Ship ship(0,0,4,3,101);

    frame.addShip(ship);
    frame.spawnShip(101);
    frame.drawMap();
    frame.printShips();
    frame.tick();
    frame.getShip(101)->actionMask.setAccelerating();
    frame.tick();
    frame.getShip(101)->actionMask.clear();
    frame.printShips();
    frame.tick();
    frame.printShips();
    frame.tick();
    frame.printShips();
    frame.tick();
    frame.printShips();
    frame.tick();
    frame.printShips();

    QPoint vector(4,4);
    int i = frame.testCanMove(vector, false, 50, 50);
    cout << i << endl;
    return 0;
}
