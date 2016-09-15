// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
#include <math.h>

Quadtree::Quadtree()
{
    root = NULL;
}

Quadtree::Quadtree(const PNG & source, int resolution)
{
    buildTree(source, resolution);
}


void Quadtree::clear(QuadtreeNode * & subRoot)
{
    if(subRoot==NULL)
    {
        return;
    }
    clear(subRoot->swChild);
    clear(subRoot->nwChild);
    clear(subRoot->neChild);
    clear(subRoot->seChild);
    delete subRoot;
    subRoot = NULL;
}

Quadtree::~Quadtree()
{
    clear(root);
}

Quadtree::Quadtree(Quadtree const & other)
{
    root = copy(other.root);
}

Quadtree::QuadtreeNode * Quadtree::copy(QuadtreeNode const * other)
{
    if(other == NULL)
    {
        return NULL;
    }
    QuadtreeNode * newNode = new QuadtreeNode(other);
    newNode->swChild = copy(other->swChild);
    newNode->nwChild = copy(other->nwChild);
    newNode->neChild = copy(other->neChild);
    newNode->seChild = copy(other->seChild);
    
    return newNode;
}

Quadtree const& Quadtree::operator=(Quadtree const & other)
{
    if(this != & other)
    {
        clear(root);
        root = copy(other.root);
    }

    return *this;
}

void Quadtree::buildTree(PNG const & source, int resolution)
{
	root = new QuadtreeNode(0, 0, resolution);
	buildTreeHelper(source, resolution, root);
}

void Quadtree::buildTreeHelper(PNG const & source, int resolution, QuadtreeNode * subNode)
{
	if(resolution == 1)
	{
		subNode->element = *source(subNode->x, subNode->y);
		return;
	}

	subNode->nwChild = new QuadtreeNode(subNode->x, subNode->y, resolution/2);
	subNode->neChild = new QuadtreeNode(subNode->x + resolution/2, subNode->y, resolution/2);
	subNode->swChild = new QuadtreeNode(subNode->x, subNode->y + resolution/2, resolution/2);
	subNode->seChild = new QuadtreeNode(subNode->x + resolution/2, subNode->y + resolution/2, resolution/2);

	buildTreeHelper(source, resolution/2, subNode->nwChild);
	buildTreeHelper(source, resolution/2, subNode->neChild);
	buildTreeHelper(source, resolution/2, subNode->swChild);
	buildTreeHelper(source, resolution/2, subNode->seChild);

	subNode->element.red = (subNode->nwChild->element.red + subNode->neChild->element.red + subNode->swChild->element.red + subNode->seChild->element.red)/4;
	
	subNode->element.green = (subNode->nwChild->element.green + subNode->neChild->element.green + subNode->swChild->element.green + subNode->seChild->element.green)/4;
	
	subNode->element.blue = (subNode->nwChild->element.blue + subNode->neChild->element.blue + subNode->swChild->element.blue + subNode->seChild->element.blue)/4;

}

RGBAPixel Quadtree::getPixel(int x, int y) const
{
    return getPixelHelper(x, y, root);
}

RGBAPixel Quadtree::getPixelHelper(int x, int y, QuadtreeNode * subNode) const
{
    if((subNode->x == x && subNode->y==y && subNode->res == 1) || (subNode->nwChild == NULL))
    {
        return subNode->element;
    }
    else if(x >= subNode->nwChild->x && x < (subNode->nwChild->x + subNode->nwChild->res) && y >= subNode->nwChild->y && y < (subNode->nwChild->y + subNode->nwChild->res))
    {
        return getPixelHelper(x,y,subNode->nwChild);
    }
    else if(x >= subNode->neChild->x && x < (subNode->neChild->x + subNode->neChild->res) && y >= subNode->neChild->y && y < (subNode->neChild->y + subNode->neChild->res))
    {
        return getPixelHelper(x,y,subNode->neChild);
    }
    else if(x >= subNode->swChild->x && x < (subNode->swChild->x + subNode->swChild->res) && y >= subNode->swChild->y && y < (subNode->swChild->y + subNode->swChild->res))
    {
        return getPixelHelper(x,y,subNode->swChild);
    }
    else if(x >= subNode->seChild->x && x < (subNode->seChild->x + subNode->seChild->res) && y >= subNode->seChild->y && y < (subNode->seChild->y + subNode->seChild->res))
    {
        return getPixelHelper(x,y,subNode->seChild);
    }
    else
    {
        return subNode->element;
    }
}

PNG Quadtree::decompress() const
{
    if(root == NULL)
    {
        return PNG();
    }
    PNG decompressed(root->res, root->res);

    for(int i = 0; i < root->res; i++)
    {
        for(int j = 0; j < root->res; j++)
        {
            *decompressed(i,j) = getPixel(i,j);
        }
    }
    return decompressed;
}

void Quadtree::clockwiseRotate()
{
   clockwiseRotate(root); 
}


void Quadtree::clockwiseRotate(QuadtreeNode * subRoot)
{

    if (subRoot->nwChild == NULL)
    {
        return;
    }
    
    QuadtreeNode * temp = subRoot->nwChild;
    subRoot->nwChild = subRoot->swChild;
    subRoot->swChild = subRoot->seChild;
    subRoot->seChild = subRoot->neChild;
    subRoot->neChild = temp;
    
	subRoot->nwChild->x = subRoot->x;
    subRoot->nwChild->y = subRoot->y;
	subRoot->neChild->x = subRoot->x + subRoot->res/2;
    subRoot->neChild->y = subRoot->y;
    subRoot->swChild->x = subRoot->x;
    subRoot->swChild->y = subRoot->y + subRoot->res/2;
    subRoot->seChild->x = subRoot->x + subRoot->res/2;
    subRoot->seChild->y = subRoot->y + subRoot->res/2;

	clockwiseRotate(subRoot->nwChild);
    clockwiseRotate(subRoot->neChild);
    clockwiseRotate(subRoot->swChild);
    clockwiseRotate(subRoot->seChild);
    
}

void Quadtree::prune(int tolerance)
{
   pruneHelper(tolerance, root); 
}

void Quadtree::pruneHelper(int tolerance, QuadtreeNode * subRoot)
{
    if (subRoot->nwChild == NULL)
    {
        return;
    }
    
    if (tolCompare(subRoot, subRoot, tolerance))
    {
        clear(subRoot->nwChild);
        clear(subRoot->neChild);
        clear(subRoot->swChild);
        clear(subRoot->seChild);
        return;
    }

    pruneHelper(tolerance,subRoot->nwChild);
    pruneHelper(tolerance,subRoot->neChild);
    pruneHelper(tolerance,subRoot->swChild);
    pruneHelper(tolerance,subRoot->seChild);
}

bool Quadtree::tolCompare(QuadtreeNode * subRoot, QuadtreeNode * average, int tol) const
{
    if (subRoot->nwChild == NULL)
    {
        return (tol >= (pow((subRoot->element.red-average->element.red), 2)+ pow((subRoot->element.green-average->element.green), 2) +pow((subRoot->element.blue-average->element.blue), 2)));
    }
    
    return  (tolCompare(subRoot->nwChild, average, tol) && tolCompare(subRoot->neChild, average, tol) && tolCompare(subRoot->swChild, average, tol) && tolCompare(subRoot->seChild, average, tol)); 
}

int Quadtree::pruneSize(int tolerance) const
{

    return pruneSizeHelper(tolerance, root);
}

int Quadtree::pruneSizeHelper(int tolerance, QuadtreeNode * subRoot) const
{
    if (subRoot->nwChild == NULL)
    {
        return 1;
    }
    if (tolCompare(subRoot, subRoot, tolerance))
    {
        return 1;
    }
    
    return pruneSizeHelper(tolerance, subRoot->nwChild) + pruneSizeHelper(tolerance, subRoot->neChild) + pruneSizeHelper(tolerance, subRoot->swChild) + pruneSizeHelper(tolerance, subRoot->seChild);
}

int Quadtree::idealPrune(int numLeaves)const
{
    int maxNum = (255*255*3);
    int minNum = 0;
    int midNum;
    while(minNum < maxNum)
    {
        midNum = (minNum + maxNum)/2;
        if(pruneSize(midNum) == numLeaves)
        {
            break;
        }
        else if(pruneSize(midNum) < numLeaves)
        {
            maxNum = midNum-1;
        }
        else
        {
            minNum = midNum + 1;
        }
    }
    while(pruneSize(midNum) == numLeaves)
    {
        midNum = midNum-1;
    }
    return midNum + 1;
}