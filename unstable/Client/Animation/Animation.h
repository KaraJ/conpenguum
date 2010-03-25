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
    /*------------------------------------------------------------------------
    -- FUNCTION NAME: setNumFrames
    --
    -- FUNCTION PURPOSE: sets the number of frame values.
    --
    -- DESIGNER: Jordan Lewis
    --
    -- PROGRAMMER: Jordan Lewis
    --
    -- DATE: March. 2nd, 2010
    -------------------------------------------------------------------------*/
    void setNumFrames(int number){numFrames_ = number;}
    /*------------------------------------------------------------------------
    -- FUNCTION NAME: setImagesWide
    --
    -- FUNCTION PURPOSE: sets images wide on texture.
    --
    -- DESIGNER: Jordan Lewis
    --
    -- PROGRAMMER: Jordan Lewis
    --
    -- DATE: March. 2nd, 2010
    -------------------------------------------------------------------------*/
    void setImagesWide(int imgcount){imagesWide_ = imgcount;}
    /*------------------------------------------------------------------------
    -- FUNCTION NAME: setImagesTall
    --
    -- FUNCTION PURPOSE: sets image count height on texture.
    --
    -- DESIGNER: Jordan Lewis
    --
    -- PROGRAMMER: Jordan Lewis
    --
    -- DATE: March. 2nd, 2010
    -------------------------------------------------------------------------*/
    void setImagesTall(int imgcount){imagesTall_ = imgcount;}
    /*------------------------------------------------------------------------
    -- FUNCTION NAME: setAnimationImages
    --
    -- FUNCTION PURPOSE: sets animation vector.
    --
    -- DESIGNER: Jordan Lewis
    --
    -- PROGRAMMER: Jordan Lewis
    --
    -- DATE: March. 2nd, 2010
    -------------------------------------------------------------------------*/
    void setAnimationImages(std::vector<Image> images){images_ = images;}
    /*------------------------------------------------------------------------
    -- FUNCTION NAME: getNumFrames
    --
    -- FUNCTION PURPOSE: returns number of frames
    --
    -- RETURN VALUE: Number of frames.
    --
    -- DESIGNER: Jordan Lewis
    --
    -- PROGRAMMER: Jordan Lewis
    --
    -- DATE: March. 2nd, 2010
    -------------------------------------------------------------------------*/
    int getNumFrames(){return numFrames_;}
    /*------------------------------------------------------------------------
    -- FUNCTION NAME: getImagesWide
    --
    -- FUNCTION PURPOSE: returns image wide count.
    --
    -- RETURN VALUE: images wide.
    --
    -- DESIGNER: Jordan Lewis
    --
    -- PROGRAMMER: Jordan Lewis
    --
    -- DATE: March. 2nd, 2010
    -------------------------------------------------------------------------*/
    int getImagesWide(){return imagesWide_;}
    /*------------------------------------------------------------------------
    -- FUNCTION NAME: getImagesTall
    --
    -- FUNCTION PURPOSE: returns image wide count.
    --
    -- RETURN VALUE: images tall.
    --
    -- DESIGNER: Jordan Lewis
    --
    -- PROGRAMMER: Jordan Lewis
    --
    -- DATE: March. 2nd, 2010
    -------------------------------------------------------------------------*/
    int getImagesTall(){return imagesTall_;}
    /*------------------------------------------------------------------------
    -- FUNCTION NAME: getAnimationImages
    --
    -- FUNCTION PURPOSE: animation image vector.
    --
    -- RETURN VALUE: animation image vector.
    --
    -- DESIGNER: Jordan Lewis
    --
    -- PROGRAMMER: Jordan Lewis
    --
    -- DATE: March. 2nd, 2010
    -------------------------------------------------------------------------*/
    std::vector<Image> getAnimationImages(){return images_;}
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
    Animation(const Animation& a);
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
    static std::map<int, Animation> getAnimationMap();
private:
   std::vector<Image> images_;

};

#endif // ANIMATION_H
