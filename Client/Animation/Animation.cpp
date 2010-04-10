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
    Animation animExplos, animExhaust, animShip, animShot;
    vector<Image> imgVecExp, imgVecExh, imgVecShip, imgVecShot;
    Image readImage;
    int mapSize = -1;
    QtXmlParse *xmlParse;
    int imagesCount = -1;
    AnimationType type = EXPLOSION;
    string typeStr;

    // get explosion animation
    string xmlFile("../Client/Animation/explosion.xml"),
    	   xmlFileExh("../Client/Animation/exhaust.xml"),
    	   xmlFileSh("../Client/Animation/wbship.xml"),
    	   xmlFileShot("../Client/Animation/shot.xml");
    xmlParse = new QtXmlParse();
    imgVecExp = xmlParse->ReadAnimationVector(type, xmlFile); // loading all Explostion animations.
    imagesCount = imgVecExp.size();
    animExplos.setAnimationImages(imgVecExp);
    // set up sound effect for animation.
	SoundEffects effectExplosion;
	effectExplosion.effectPath_ = imgVecExp.front().soundLink;
	effectExplosion.type_ = explosion;

	//effectExplosion->SetSoundSource((char*)animationExplosion.front().soundLink.c_str(), explosion);
	animExplos.setSoundEffect(effectExplosion);
    //animationEx.soundFile = animationExplosion.front().soundLink; // link sound from animation.
    animations.insert(std::pair<int, Animation>((int)type, animExplos));

    // get ship animation
    type = SHIP;
	imgVecShip = xmlParse->ReadAnimationVector(type, xmlFileSh); // loading all Explostion animations.
	imagesCount = imgVecShip.size();
	animShip.setAnimationImages(imgVecShip);
	//animationSh.soundFile = animationShip.front().soundLink; // link sound from animation.
	animShip.numFrames_ = imgVecShip.front().numFrames; // link sound from animation.
	animShip.imagesTall_ = imgVecShip.front().imagesTall; // link sound from animation.
	animShip.imagesWide_ = imgVecShip.front().imagesWide; // link sound from animation.
	animations.insert(std::pair<int, Animation>((int)type, animShip));

    // get ship animation
    type = SHOT;
	imgVecShot = xmlParse->ReadAnimationVector(type, xmlFileShot); // loading all Explostion animations.
	imagesCount = imgVecShot.size();
	animShot.setAnimationImages(imgVecShot);
	//animationSh.soundFile = animationShip.front().soundLink; // link sound from animation.
	animShot.numFrames_ = imgVecShot.front().numFrames; // link sound from animation.
	animShot.imagesTall_ = imgVecShot.front().imagesTall; // link sound from animation.
	animShot.imagesWide_ = imgVecShot.front().imagesWide; // link sound from animation.
	animations.insert(std::pair<int, Animation>((int)type, animShot));

    // get trail animations.
    type = EXHAUST;
    imgVecExh = xmlParse->ReadAnimationVector(type, xmlFileExh);
    imagesCount = imgVecExh.size();
    animExhaust.setAnimationImages(imgVecExh);
    SoundEffects effectExhaust;
    effectExhaust.effectPath_ = imgVecExh.front().soundLink;
    effectExhaust.type_ = exhaust;
    animExhaust.setSoundEffect(effectExhaust);
    //animationExh.soundFile = animationExhaust.front().soundLink; // link sound from animation.
	animations.insert(std::pair<int, Animation>((int)type, animExhaust));

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
}
