#include "Animation.h"
using namespace std;
/*----------------------------------------------------------------------------------------------
-- FUNCTION NAME: Animation
--
-- PURPOSE: Constructor.
--
-- DESIGNER: Jordan 
--
-- PROGRAMMER: Jordan
--
-- DATE: Jan. 31st, 2010
--
-- REVISIONS: None
-----------------------------------------------------------------------------------------------*/
Animation::Animation()
{
/* do nothing yet */
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION NAME: setXOffSet
--
-- PURPOSE: sets the XOffSet, will go into the Image class.
--
-- DESIGNER: Jordan 
--
-- PROGRAMMER: Jordan
--
-- DATE: Jan. 31st, 2010
--
-- REVISIONS: None
-----------------------------------------------------------------------------------------------*/
void Animation::setXOffSet(int xOffSet)
{
	xOffSet_ = xOffSet;
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION NAME: setYOffSet
--
-- PURPOSE: sets the yOffSet, will go into the Image class.
--
-- DESIGNER: Jordan 
--
-- PROGRAMMER: Jordan
--
-- DATE: Jan. 31st, 2010
--
-- REVISIONS: None
-----------------------------------------------------------------------------------------------*/
void Animation::setYOffSet(int yOffSet)
{
	yOffSet_ = yOffSet;
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION NAME: setFileLocation
--
-- PURPOSE: sets the location of the texture file.
--
-- DESIGNER: Jordan 
--
-- PROGRAMMER: Jordan
--
-- DATE: Jan. 31st, 2010
--
-- REVISIONS: None
-----------------------------------------------------------------------------------------------*/
void Animation::setFileLocation(string location)
{
	fileLocation_ = location;
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION NAME: buildAnimationVector
--
-- PURPOSE: builds vector of images used in animations.
--
-- DESIGNER: Jordan 
--
-- PROGRAMMER: Jordan
--
-- DATE: Jan. 31st, 2010
--
-- REVISIONS: None
-----------------------------------------------------------------------------------------------*/
vector<Image> Animation::buildAnimationVector(AnimationType type)
{
	/* VECTOR will be of images(class to be implemented), which will be stored within the animation. vector 
	will have to be added to animation class. for each animation type this 
	function will build the actual offset and return the vector for the animation.*/
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION NAME: loadAnimationImages
--
-- PURPOSE: loads an image based on the type of animation. We need to figure out how to handle
--          the iteration through images and offset.
--
-- DESIGNER: Jordan 
--
-- PROGRAMMER: Jordan
--
-- DATE: Jan. 31st, 2010
--
-- REVISIONS: None
-----------------------------------------------------------------------------------------------*/
string Animation::loadAnimationImages(AnimationType type)
{
	/*
		will be used to Create Image objects. Images objects based on type. Offsets will be stored within image.
		Images will be stored in a vector in the build animation vector. We will return images from this function.
	*/
}
