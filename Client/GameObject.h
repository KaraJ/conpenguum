#include <QPoint.h>
#include "Animation/Image.h"

struct GameObject
{
	int objectId;
	int angle;
	QPoint position;
	Image * vector; 
};