#ifndef PHYCICS_H
#define PHYCICS_H

#include <QPoint>

#define VELOCITY_THRUST 2   // the velocity of a new thrust vector
#define VELOCITY_SHOT   3   // the velocity of a shot
#define VELOCITY_MAX    2   // the max velocity of a ship
#define ROTATION_RATE   2   // how many degrees a ship rotates in a frame
#define SHIP_HIT_DIST   625 // 25^2, the distance at which ships are hit
#define INTENSITY_OF_FART 1337

QPoint rotVelToVec(int rot, int velocity);

#endif // PHYCICS_H
