#include "Image.h"
using namespace std;
/*----------------------------------------------------------------------------------------------
-- FUNCTION NAME: Image
--
-- PURPOSE: constructor.
--
-- DESIGNER: Jordan 
--
-- PROGRAMMER: Jordan
--
-- DATE: Jan. 31st, 2010
--
-- REVISIONS: None
-----------------------------------------------------------------------------------------------*/
Image::Image(int xOff, int yOff, string texturePath)
{
	xOffSet_ = xOff; 
	yOffSet_ = yOff; 
	texturePath_ = texturePath; 
} 
