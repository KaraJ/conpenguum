#include <iostream>
#include <QPoint>
#include "physics.h"
#include "frame.h"
#include "ship.h"

using namespace std;
int main() {
    Frame frame;
    Ship ship(0,0,0,0,101);
    frame.addShip(ship);
    frame.spawnShip(101);
    frame.printShips();
    return 0;
}
