#include <cstdlib>
#include <iostream>
#include "png.h"
using namespace std;

// sets up the output image
PNG * setupOutput(int w, int h);

// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity);

int main()
{
	// Load in.png
	PNG * original;
	original = new PNG; //The error here was that original was not pointing to anything intially
	original->readFromFile("in.png");
	int width  = original->width();
	int height = original->height();

	// Create out.png
	//output = setUpOutput or else output is just sitting there same problem as up there^^
	PNG * output;
	output = setupOutput(width, height);

	// Loud our favorite color to color the outline
	RGBAPixel * myPixel = myFavoriteColor(192);

	// Go over the whole image, and if a pixel differs from that to its upper
	// left, color it my favorite color in the output
	//y>0 and x>0
	for (int y = 1; y > 0 && y < height; y++)
	{
		for (int x = 1;  x>0 && x < width; x++)
		{
			// Calculate the pixel difference
			RGBAPixel * prev = (*original)(x-1, y-1);
			RGBAPixel * curr = (*original)(x  , y  );
			int diff = abs(curr->red   - prev->red  ) +
					   abs(curr->green - prev->green) +
					   abs(curr->blue  - prev->blue );

			// If the pixel is an edge pixel,
			// color the output pixel with my favorite color
			RGBAPixel * currOutPixel = (*output)(x,y);
			if (diff > 100)
				*currOutPixel = *myPixel;
		}
	}
	
	// Save the output file
	output->writeToFile("out.png");

	// Clean up memory
	delete myPixel;
	delete output;
	delete original;
	//need NULL to free memory?
	return 0;
}


// sets up the output image
PNG * setupOutput(int w, int h)
{
	PNG * image = new PNG(w, h);
	return image;
}


// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity)
{
	RGBAPixel* color;
	color = new RGBAPixel;

	color->red   = 0;
	color->green = intensity/2;
	color->blue  = intensity;
	return color;

}
