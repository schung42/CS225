#include "rgbapixel.h"

//creates default opaque RGBAPixel
RGBAPixel::RGBAPixel()
{
	red = 255;
	green = 255;
	blue = 255;
	alpha = 255;
}

RGBAPixel::RGBAPixel(unsigned char red, unsigned char green, unsigned char blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	alpha = 255;
}
