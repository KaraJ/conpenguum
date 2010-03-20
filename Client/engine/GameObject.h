#include <QPoint>
#include "../Animation/Image.h"

struct GameObject
{
	int objectId;
	int angle;
	QPoint position;
	Image * animeImage;
	int animeIndex;
};