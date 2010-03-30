#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include "Image.h"
#include <map>
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
public:
    int numFrames_, imagesWide_, imagesTall_;
    Animation()
    {
        numFrames_ = 0;
        imagesWide_ = 0;
        imagesTall_ = 0;
    }
    void setNumFrames(int number){numFrames_ = number;}
    void setImagesWide(int imgcount){imagesWide_ = imgcount;}
    void setImagesTall(int imgcount){imagesTall_ = imgcount;}
    void setAnimationImages(std::vector<Image> images){images_ = images;}
    int getNumFrames(){return numFrames_;}
    int getImagesWide(){return imagesWide_;}
    int getImagesTall(){return imagesTall_;}
    std::vector<Image> &getAnimationImages(){return images_;}
    Animation(const Animation& a);
    std::string soundFile;
    static std::map<int, Animation> getAnimationMap();
private:
   std::vector<Image> images_;

};

#endif // ANIMATION_H
