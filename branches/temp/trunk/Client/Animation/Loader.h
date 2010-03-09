#ifndef LOADER_H
#define LOADER_H
#include "Animation.h"
#include <vector>
#include <string>
#include <map>
/*----------------------------------------------------------------------------------------------
-- CLASSNAME: Loader
--
-- PURPOSE: used to load animations for later release to gameplay.
--
-- DESIGNER: Jordan 
--
-- PROGRAMMER: Jordan
--
-- DATE: Jan. 31st, 2010
--
-- REVISIONS: None
-----------------------------------------------------------------------------------------------*/
class Loader
{
	public:
		Loader(); /* defined in .cpp */
		Animation getAnimation(AnimationType type);
	private: 
		Animation anim_[NUMBER_OF_ANIMATIONS];
		std::map<std::string, std::string> textureStorage_; /* will later map animation name to Animation object*/
};
#endif
