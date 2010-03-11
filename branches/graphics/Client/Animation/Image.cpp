#include "Image.h"

/*------------------------------------------------------------------------
-- FUNCTION NAME: Image() - constructor.
--
-- FUNCTION PURPOSE: initializes image offsets and state data.
--
-- DESIGNER: Jordan Lewis
--
-- PROGRAMMER: Jordan Lewis
--
-- DATE: March. 2nd, 2010
-------------------------------------------------------------------------*/
Image::Image()
{
    leftOffSet_ = 0.0f;
    rightOffSet_ = 0.0f;
    topOffSet_ = 0.0f;
    bottomOffSet_ = 0.0f;
    width_ =  0.0f;
    height_ =  0.0f;
}
void Image::setDescription(std::string desc)
{

}

