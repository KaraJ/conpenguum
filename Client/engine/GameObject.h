#ifndef GAMESOBJECT_H
#define GAMESOBJECT_H
#include <QPoint>
#include <vector>
#include <qstring.h>
#include "../Animation/Animation.h"
#include "../Animation/Image.h"

//0 ~ 65536

struct GameObject
{
	int objectId;
	int angle;
        int animFrame;
        QString text;
	QPoint position;
	Image * animeImage;
        Animation currentAnime;
	size_t animeIndex;
};

#endif
