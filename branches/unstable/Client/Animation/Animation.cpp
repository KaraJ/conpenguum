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
    Animation animation;
    vector<Image> vImage;
    SoundEffects sEffect;
    QtXmlParse *xmlParse = new QtXmlParse();;
    RESOURCETYPES type;
    string xmlFile;

    // get explosion animation
    type = EXPLOSION;
    xmlFile = "../Client/Animation/explosion.xml";
    vImage = xmlParse->ReadAnimationVector(xmlFile);
    sEffect.effectPath_ = vImage.front().soundLink;
    sEffect.type_ = (SoundEffects::SOUNDTYPE)type;
    animation.numFrames_  = vImage.front().numFrames; // link sound from animation.
    animation.imagesTall_ = vImage.front().imagesTall; // link sound from animation.
    animation.imagesWide_ = vImage.front().imagesWide; // link sound from animation.
    animation.setAnimationImages(vImage);
    animation.setSoundEffect(sEffect);
    animations.insert(std::pair<int, Animation>((int)type, animation));

    // get ship animation
    type = SHIP;
    xmlFile = "../Client/Animation/wbship.xml";
    vImage = xmlParse->ReadAnimationVector(xmlFile);
	animation.numFrames_  = vImage.front().numFrames; // link sound from animation.
	animation.imagesTall_ = vImage.front().imagesTall; // link sound from animation.
	animation.imagesWide_ = vImage.front().imagesWide; // link sound from animation.
	animation.setAnimationImages(vImage);
	animations.insert(std::pair<int, Animation>((int)type, animation));

    // get shot animation
	xmlFile = "../Client/Animation/shot.xml";
    type = SHOT;
    vImage = xmlParse->ReadAnimationVector(xmlFile);
	animation.numFrames_  = vImage.front().numFrames; // link sound from animation.
	animation.imagesTall_ = vImage.front().imagesTall; // link sound from animation.
	animation.imagesWide_ = vImage.front().imagesWide; // link sound from animation.
	animation.setAnimationImages(vImage);
	animations.insert(std::pair<int, Animation>((int)type, animation));

    // get trail animations.
	xmlFile = "../Client/Animation/exhaust.xml";
    type = EXHAUST;
    vImage = xmlParse->ReadAnimationVector(xmlFile);
	sEffect.effectPath_ = vImage.front().soundLink;
	sEffect.type_ = (SoundEffects::SOUNDTYPE) type;
	animation.numFrames_  = vImage.front().numFrames; // link sound from animation.
	animation.imagesTall_ = vImage.front().imagesTall; // link sound from animation.
	animation.imagesWide_ = vImage.front().imagesWide; // link sound from animation.
	animation.setAnimationImages(vImage);
	animation.setSoundEffect(sEffect);
	animations.insert(std::pair<int, Animation>((int)type, animation));

	// get powerup animations
	xmlFile = "../Client/Animation/powerups.xml";
	type = AIDBOX;
	vImage = xmlParse->ReadAnimationVector(xmlFile);
	animation.numFrames_  = vImage.front().numFrames; // link sound from animation.
	animation.imagesTall_ = vImage.front().imagesTall; // link sound from animation.
	animation.imagesWide_ = vImage.front().imagesWide; // link sound from animation.
	animation.setAnimationImages(vImage);
	animations.insert(std::pair<int, Animation>((int)type, animation));

    return animations;
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
