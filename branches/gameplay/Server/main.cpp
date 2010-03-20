#include <iostream>
#include <QPoint>
#include "physics.h"
#include "frame.h"
#include "ship.h"
#include "clientaction.h"

using namespace std;
int main() {
    ClientAction actionMask(0);
    actionMask.setAccelerating();
    actionMask.setTurningLeft();
    Frame frame("map.xml");
    Ship ship01, ship02;
    frame.addShip(ship01);
    frame.addShip(ship02);
    frame.printShips();
    frame.spawnShip(0);
    frame.printShips();
    frame.getShip(0)->applyActionMask(actionMask);
    frame.tick();
    frame.printShips();
    frame.tick();
    frame.printShips();
    actionMask.clear();
    frame.getShip(0)->applyActionMask(actionMask);
    frame.tick();
    frame.printShips();
    
    QPoint tPoint = QPoint(4,4);
    
    
    cout << "THE TEST!" << endl << frame.map.canMove(tPoint, true, 50, 0) << endl;
    
    return 0;
}
