#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
#include <vector>
#include "Image.h"
#include <map>
#include "../SoundEffects/SoundEffects.h"
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
    SoundEffects soundEffect_; // holds the sound effect for this animation.
public:
    Animation()
    {
        numFrames_ = 0;
        imagesWide_ = 0;
        imagesTall_ = 0;
    }
    Animation(const Animation& a);
    void setNumFrames(int number){numFrames_ = number;}
    void setImagesWide(int imgcount){imagesWide_ = imgcount;}
    void setImagesTall(int imgcount){imagesTall_ = imgcount;}
    void setAnimationImages(std::vector<Image> images){images_ = images;}
    int getNumFrames(){return numFrames_;}
    int getImagesWide(){return imagesWide_;}
    int getImagesTall(){return imagesTall_;}
    std::vector<Image> *getAnimationImages(){return &images_;}

    static std::map<int, Animation> getAnimationMap();
    void setSoundEffect(SoundEffects effect)
    {
    	soundEffect_ = effect;
    	//soundEffect_.effectPath_ = effect.effectPath_;
    	//soundEffect_.type_ = effect.type_;
    	//soundEffect_->soundEffect_ = effect->soundEffect_;
    	//soundEffect_->SetSoundSource(effect->GetSoundSource().c_str(), effect->GetType());

    }
    SoundEffects getSoundEffect(){return soundEffect_;}


};

#endif
