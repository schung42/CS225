#ifndef MYFILE_H
#define MYFILE_H

#include "image.h"


class Scene{

public:

int max;
Image ** arraylayer;
int * x_array;
int * y_array;


//set up Scene to hold "max" images 
Scene(int max);


//frees the dynamically allocated space
~Scene();


// copy function
void copy(const Scene &source);

//clears
void clear();

//the copy constructor makes this scene and independent copy of the source
Scene (const Scene &source);

// assignment operator for the Scene class
const Scene & operator = (const Scene &source);

//changes the size of the array of the image pointers without altering the indices
void changemaxlayers (int newmax);

//add a picture to the scene by placing it in the array cell corresponding to the given index and storing its x coordinate and y coordinate
void addpicture(const char *FileName, int index, int x, int y);

//Moves an image from one layer to another
void changelayer(int index, int newindex);

//changes the x and y coordinates of the image in the specified layer
void translate(int index, int xcoord, int ycoord);

//deletes image at given index
void deletepicture(int index);

//returns a pointer to the image at a specific index
Image * getpicture(int index) const;

//draws the scene and returns the image value
Image drawscene() const;

};

#endif
