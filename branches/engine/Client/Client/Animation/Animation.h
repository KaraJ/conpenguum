#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
#include <vector>
#include "Image.h"
#define NUMBER_OF_ANIMATIONS 5 /*referes to AnimationType definition below*/
enum AnimationType
{
	THRUST, BANK_LEFT, BANK_RIGHT, HIT, FIRE
};
/*----------------------------------------------------------------------------------------------
-- CLASSNAME: Animation
--
-- PURPOSE: used to retain vector of animation snap shots. Also retains related speed of animation
--          as well as type.
--
-- DESIGNER: Jordan 
--
-- PROGRAMMER: Jordan
--
-- DATE: Jan. 31st, 2010
--
-- REVISIONS: None
-----------------------------------------------------------------------------------------------*/
class Animation
{
	public: 
		Animation();/*implemented in .cpp file*/
		~Animation(){}/*destructor*/
		int getXOffSet(){return xOffSet_;}
		int getYOffSet(){return yOffSet_;}
		std::vector<Image> buildAnimationVector(AnimationType type);
		std::string loadAnimationImages(AnimationType type); /* will have to return some sort of image type */
		std::string getFileLocation(){return fileLocation_;}
		void setXOffSet(int xOffSet); /*implemented in .cpp file*/
		void setYOffSet(int yOffSet); /*implemented in .cpp file*/
		void setFileLocation(std::string location); /*implemented in .cpp file*/
		
	private:
		std::string fileLocation_; 
		std::vector<Image> images_; /* stores vector of images */
		int xOffSet_, yOffSet_;
		int animationSpeed; /* will be used to control the speed of the animation based on type. */
		AnimationType type; /* hold type of animation */
};

#endif
