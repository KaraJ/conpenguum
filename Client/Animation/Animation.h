#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
#include <vector>
#include <map>
#include <phonon/mediaobject.h>


#include "Image.h"

/*------------------------------------------------------------------------
-- CLASS NAME: Animation
--
-- CLASS PURPOSE: Copy constructor for loading into map.
--
--
-- DESIGNER: Jordan Lewis
--
-- PROGRAMMER: Jordan Lewis
--
-- DATE: March. 2nd, 2010
-------------------------------------------------------------------------*/

class Animation
{
private:
    int numFrames_, imagesWide_, imagesTall_;
    std::vector<Image> images_;
    Phonon::MediaObject* sound_;
    bool hasSound_;
    static Animation makeAnimation(std::string xml);
public:
    Animation():numFrames_(0), imagesWide_(0), imagesTall_(0), hasSound_(false){}
    void setNumFrames(int number){numFrames_ = number;}
    void setImagesWide(int imgcount){imagesWide_ = imgcount;}
    void setImagesTall(int imgcount){imagesTall_ = imgcount;}
    void setAnimationImages(std::vector<Image> images){images_ = images;}
    int getNumFrames(){return numFrames_;}
    int getImagesWide(){return imagesWide_;}
    int getImagesTall(){return imagesTall_;}
    bool hasSound(){return hasSound_;}
    Phonon::MediaObject* getSound(){return sound_;}
    std::vector<Image>* getAnimationImages(){return &images_;}

    static std::map<int, Animation> getAnimationMap();


};

#endif
