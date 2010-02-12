#ifndef IMAGE_H
#define IMAGE_H
#include <string>
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
		explicit Image(int, int, std::string);
	private:
		/* Need to have a way of actually storing the image within this image object. 
		   will allow us to manipulate the offsets of texture image. */
		int xOffSet_, yOffSet_; 
		std::string texturePath_;
		
	
};
#endif
