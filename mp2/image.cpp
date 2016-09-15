#include "image.h"
#include <iostream>

void Image :: flipleft()
{
	for(size_t x=0; x< width()/2;x++)
	{
		for(size_t y=0; y<height();y++)
		{
			RGBAPixel filler = *(*this)(x,y);
			*(*this)(x,y) = *(*this)(width()-x-1, y);
			*(*this)(width()-x-1,y) = filler;
		}
	}
}

void Image :: adjustbrightness(int r, int g, int b)
{
	for(size_t x=0; x <width(); x++)
	{
		for(size_t y=0; y<height(); y++)
		{
			if(((*this)(x,y) -> red+r)>255)
				(*this)(x,y) -> red = 255;
			else if(((*this)(x,y) -> red+r)<0)
				(*this)(x,y) -> red =0;
			else(*this)(x,y) -> red = (*this)(x,y) ->red+r;
				
			if(((*this)(x,y) -> green+g)>255)
				(*this)(x,y) -> green = 255;
			else if(((*this)(x,y) -> green+g)<0)
				(*this)(x,y) -> green =0;
			else(*this)(x,y) -> green = (*this)(x,y) ->green+g;
				
			if(((*this)(x,y) -> blue+b)>255)
				(*this)(x,y) -> blue = 255;
			else if(((*this)(x,y) -> blue+b)<0)
				(*this)(x,y) -> blue =0;
			else(*this)(x,y) -> blue = (*this)(x,y) ->blue+b;
			
		}
	}
}

void Image :: invertcolors()
{
	for(size_t x = 0; x<width(); x++)
	{
		for(size_t y = 0; y<height(); y++)
		{
			(*this)(x,y)->red = (255-((*this)(x,y)->red));
			(*this)(x,y)->green = (255-((*this)(x,y)->blue));
			(*this)(x,y)->blue = (255-((*this)(x,y)->green));
			
		}
	}
}


