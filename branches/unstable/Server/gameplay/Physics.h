#ifndef PHYCICS_H
#define PHYCICS_H

#include <QVector2D>

#define VELOCITY_THRUST 1   // the velocity of a new thrust vector
#define VELOCITY_SHOT   10   // the velocity of a shot
#define VELOCITY_MAX    32   // the max velocity of a ship^2
#define RVELOCITY_MAX   25  //  the reverse velocity
#define ROTATION_RATE   1   // how many degrees a ship rotates in a frame
#define SHIP_HIT_DIST   400 // 20^2, the distance at which ships are hit
#define SHIPRADIUS      20  // the radius of a ships "tile".
#define SHOTSPAWNRAD    (SHIPRADIUS + 1)
#define SHIPSIZE        (SHIPRADIUS * 2)
#define TILE_SIZE       25  // the size of a side of a tile.

//PI macros
#define PI              3.14159265358979323846
#define TWOPI           (2.0 * PI)
#define INVERSEPI       0.31830988618379067154

//vector magnitude
#define VECTORMAGNITUDE(a)    (  ( a.x()*a.x() ) + ( a.y()*a.y() )  )

QVector2D rotVelToVec(int rot, int velocity);

#endif // PHYCICS_H
