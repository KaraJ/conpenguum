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
-- DATE: March. 2nd, 2010
-------------------------------------------------------------------------*/
map<int, Animation> Animation::getAnimationMap()
{
    map<int, Animation> animations;
    Animation animationEx, animationExh, animationSh;
    vector<Image> animationExplosion, animationExhaust, animationShip;
    Image readImage;
    int mapSize = -1;
    QtXmlParse *xmlParse;
    int imagesCount = -1;
    AnimationType type = EXPLOSION;
    string typeStr;

    // get explosion animation
    string xmlFile("../Client/Animation/explosion.xml"), xmlFileExh("../Client/Animation/exhaust.xml"), xmlFileSh("../Client/Animation/ship.xml");
    xmlParse = new QtXmlParse();
    animationExplosion = xmlParse->ReadAnimationVector(type, xmlFile); // loading all Explostion animations.
    imagesCount = animationExplosion.size();
    animationEx.setAnimationImages(animationExplosion);
    // set up sound effect for animation.
	SoundEffects effectExplosion;
	effectExplosion.effectPath_ = animationExplosion.front().soundLink;
	effectExplosion.type_ = explosion;

	//effectExplosion->SetSoundSource((char*)animationExplosion.front().soundLink.c_str(), explosion);
	animationEx.setSoundEffect(effectExplosion);
    //animationEx.soundFile = animationExplosion.front().soundLink; // link sound from animation.
    animations.insert(std::pair<int, Animation>((int)type, animationEx));

    // get ship animation
    type = SHIP;
	animationShip = xmlParse->ReadAnimationVector(type, xmlFileSh); // loading all Explostion animations.
	imagesCount = animationShip.size();
	animationSh.setAnimationImages(animationShip);
	//animationSh.soundFile = animationShip.front().soundLink; // link sound from animation.
	animationSh.numFrames_ = animationShip.front().numFrames; // link sound from animation.
	animationSh.imagesTall_ = animationShip.front().imagesTall; // link sound from animation.
	animationSh.imagesWide_ = animationShip.front().imagesWide; // link sound from animation.
	animations.insert(std::pair<int, Animation>((int)type, animationSh));

    // get trail animations.
    type = EXHAUST;
    animationExhaust = xmlParse->ReadAnimationVector(type, xmlFileExh);
    imagesCount = animationExhaust.size();
    animationExh.setAnimationImages(animationExhaust);
    SoundEffects effectExhaust;
    effectExhaust.effectPath_ = animationExhaust.front().soundLink;
    effectExhaust.type_ = exhaust;
    animationExh.setSoundEffect(effectExhaust);
    //animationExh.soundFile = animationExhaust.front().soundLink; // link sound from animation.
	animations.insert(std::pair<int, Animation>((int)type, animationExh));

    mapSize = (int)animations.size();

    return (animations);
}
/*------------------------------------------------------------------------
-- FUNCTION NAME: Animation()
--
-- FUNCTION PURPOSE: Copy constructor for loading into map.
--
-- RETURN VALUE: Nothing.
--
-- DESIGNER: Jordan Lewis
--
-- PROGRAMMER: Jordan Lewis
--
-- DATE: March. 2nd, 2010
-------------------------------------------------------------------------*/
Animation::Animation(const Animation &a)
{
    images_ = a.images_;
    numFrames_ = a.numFrames_;
    imagesWide_ = a.imagesWide_;
    imagesTall_ = a.imagesTall_;
   //images_ = a.getAnimationImages();
   //numFrames_ = a.getNumFrames();
   //imagesWide_ = a.getImagesWide();
   //imagesTall_ = a.getImagesTall();
}
