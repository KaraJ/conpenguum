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
    vector<Image> animationExplosion, animationShip;
    Image readImage;
    int mapSize = -1;
    int imagesCount = -1;
    AnimationType type = Explosion;
    string typeStr;
    string xmlFile("./explosion.xml");
    QtXmlParse *xmlParse = new QtXmlParse();
    animationExplosion = xmlParse->ReadAnimationVector(type, xmlFile); // loading all Explostion animations.
    imagesCount = animationExplosion.size();
    animation.setAnimationImages(animationExplosion);
    animations.insert(std::pair<int, Animation>((int)type, animation));

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
