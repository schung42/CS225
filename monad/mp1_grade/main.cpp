#include "png.h"

PNG rotate180(PNG pngInput);

int main()
{
	PNG image("in.png");
	image = rotate180(image);
	image.writeToFile("out.png");
	return 0;
}

//rotate 180 degrees

PNG rotate180(PNG pngInput)
{
	for(size_t y = 0; y<pngInput.height()/2; y++)
		{
			for(size_t x = 0; x< pngInput.width();x++)
			{
				RGBAPixel filler = *pngInput(x,y);
				*pngInput(x,y) = *pngInput(pngInput.width()-x-1, pngInput.height()-y-1);
				*pngInput(pngInput.width()-x-1, pngInput.height()-y-1) = filler;
			}
		}
	
	if(pngInput.height()%2 !=0)
	{
		size_t y = pngInput.height()/2;
		
		for(size_t x = 0; x<pngInput.width()/2; x++)
		{
			RGBAPixel filler = *pngInput(x,y);
			*pngInput(x,y) = *pngInput(pngInput.width()-x-1, y);
			*pngInput(pngInput.width()-x-1, y)= filler;
		}
	}
	return pngInput;
}
