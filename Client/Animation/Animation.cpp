#include "Animation.h"
#include "qtxmlparse.h"

using namespace std;

/*------------------------------------------------------------------------
-- FUNCTION NAME: getAnimationMap()
--
-- FUNCTION PURPOSE: Static method to generate animation map.
--
-- RETURN VALUE: Map of animations (map<int, Animation> where int is the enum
--               for animation type found in AnimationEnum)
--
-- DESIGNER: Jordan Lewis
--
-- PROGRAMMER: Jordan Lewis
--
-- REVISIONS: Kara Martens - Refactored the animation creation into a method.
--
-- DATE: March. 2nd, 2010
-------------------------------------------------------------------------*/
map<int, Animation> Animation::getAnimationMap()
{
    map<int, Animation> animations;

    animations.insert(std::pair<int, Animation>((int)EXPLOSION, makeAnimation("Animation/explosion.xml")));
	animations.insert(std::pair<int, Animation>((int)SHIP, makeAnimation("Animation/wbship.xml")));
	animations.insert(std::pair<int, Animation>((int)SHOT, makeAnimation("Animation/shot.xml")));
	animations.insert(std::pair<int, Animation>((int)EXHAUST, makeAnimation("Animation/exhaust.xml")));
	animations.insert(std::pair<int, Animation>((int)AIDBOX, makeAnimation("Animation/powerups.xml")));

    return animations;
}

Animation Animation::makeAnimation(std::string xml)
{
	Animation animation;
    vector<Image> vImage;
    QtXmlParse *xmlParse = new QtXmlParse();

	vImage = xmlParse->ReadAnimationVector(xml);
	animation.numFrames_  = vImage.front().numFrames;
	animation.imagesTall_ = vImage.front().imagesTall;
	animation.imagesWide_ = vImage.front().imagesWide;
	animation.setAnimationImages(vImage);
	if(vImage.front().soundLink != "")
	{
	    animation.hasSound_ = true;
	    animation.sound_ = Phonon::createPlayer(Phonon::GameCategory, Phonon::MediaSource(QString::fromStdString(vImage.front().soundLink)));
	}
	return animation;
}
