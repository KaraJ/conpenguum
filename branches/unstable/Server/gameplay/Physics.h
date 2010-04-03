#ifndef PHYCICS_H
#define PHYCICS_H

#include <QVector2D>

#define VELOCITY_THRUST 2   // the velocity of a new thrust vector
#define VELOCITY_SHOT   15   // the velocity of a shot
#define VELOCITY_MAX    64   // the max velocity of a ship^2
#define ROTATION_RATE   2   // how many degrees a ship rotates in a frame
#define SHIP_HIT_DIST   400 // 20^2, the distance at which ships are hit
#define SHIPRADIUS      20  // the radius of a ships "tile".
#define SHIPSIZE        SHIPRADIUS * 2
#define TILE_SIZE       25  // the size of a side of a tile.

//PI macros
#define PI              3.14159265358979323846
#define TWOPI           (2.0 * PI)
#define INVERSEPI       0.31830988618379067154

//Degree macros
#define RADIANSINDEG   	0.017453293 //PI/180
#define DEGREESINRAD    57.295779513 //180/PI
#define DEGTORAD(a)     ((a)*RADIANSINDEG)
#define RADTODEG(a)         ((a)*DEGREESINRAD)

//vector magnitude
#define VECTORMAGNITUDE(a)    (  ( a.x()*a.x() ) + ( a.y()*a.y() )  )

QVector2D rotVelToVec(int rot, int velocity);

#endif // PHYCICS_H
