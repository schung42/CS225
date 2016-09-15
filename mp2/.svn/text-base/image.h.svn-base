#ifndef IMAGE_H
#define IMAGE_H

#include "png.h"

class Image : public PNG
{
	public:
	
		//Flips the image about a vertical line through its center by swapping pixels
		void flipleft();
		
		//Adds to the red, green, and blue parts of each pixel in the image
		void adjustbrightness(int r, int g, int b);
		
		//Makes each RGB component of each pixel equal to 255 minus its original value
		void invertcolors();
};

#endif
