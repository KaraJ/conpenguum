#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <iostream>

/*----------------------------------------------------------------------------------------------
-- CLASSNAME: Image
--
-- PURPOSE: used to retain a animation still image. Texture x and y offsets will be used to
--          capture animation still. We will need to determine image sizes.
--
-- DESIGNER: Jordan
--
-- PROGRAMMER: Jordan
--
-- DATE: Jan. 31st, 2010
--
-- REVISIONS: None
-----------------------------------------------------------------------------------------------*/
class Image
{
public:
		//explicit Image(int, int, std::string);
		Image();
		float getLeftOffSet(){return leftOffSet_;}
		float getRightOffSet(){return rightOffSet_;}
		float getTopOffSet(){return topOffSet_;}
		float getBottomOffSet(){return bottomOffSet_;}
		void setWidth(int width){width_ = width;}
		void setHeight(int height){height_ = height;}
		int getHeight(){return height_;}
		int getWidth(){return width_;}
		void setLeftOffSet(float offset){leftOffSet_ = offset;}
		void setRightOffSet(float offset){rightOffSet_ = offset;}
		void setTopOffSet(float offset){topOffSet_ = offset;}
		void setBottomOffSet(float offset){bottomOffSet_ = offset;}
		void setDescription(std::string desc);
		void setLink(std::string link){ texturePath_ = link; }
		void setDirection(int dir){direction_ = dir;}
		int getDirection(){return direction_;}
		std::string getDescription(){return description_;}
		std::string soundLink;

private:
		/* Need to have a way of actually storing the image within this image object.
		   will allow us to manipulate the offsets of texture image. */
		float leftOffSet_, rightOffSet_, topOffSet_, bottomOffSet_, width_, height_;// percent offset
		std::string description_;
		std::string texturePath_;
		int direction_;
};
#endif

