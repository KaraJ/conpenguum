#include "Physics.h"

#include <QPoint>
#include <math.h>

#include "../../Core/comm/globals.h"

/*-----------------------------------------------------------------------------
--  FUNCTION:   rotVelToVec
--
--  DATE:       February 18, 2010
--
--  REVISIONS:  v0.1
--
--  DESIGNER:   Gameplay/Physics Team
--
--  PROGREMMER: Gameplay/Physics Team
--
--  INTERFACE:  rotVelToVec(int rot, int velocity)
--
--  NOTES:      Takes a rotation value and a velocity and returns the correct
--              vector. TASK: needs to be made more efficient.
--
--  RETURNS:    Qpoint style vector.
--
------------------------------------------------------------------------------*/
QVector2D rotVelToVec(int rot, double velocity)
{
    QVector2D vector;
    //correcting the function here and removing the magic number
    double radians = DEGTORAD(rot);
    double x, y;
    y = sin(radians) * velocity;
    x = cos(radians) * velocity;
    vector.setX(x);
    vector.setY(y);
    return vector;
}

