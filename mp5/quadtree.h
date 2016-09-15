// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
	
	Quadtree();

	Quadtree(const PNG & source, int resolution);
	
	Quadtree(Quadtree const & other);
	
	//destructor
	~Quadtree();

	//functions and their helpers

	void buildTree (PNG const & source, int resolution);
	Quadtree const & operator= (Quadtree const &other);
	RGBAPixel getPixel(int x, int y)const;
	void clockwiseRotate();
	PNG decompress() const;
	int pruneSize(int tolerance) const;
	void prune(int tolerance);
	int idealPrune(int numLeaves) const;
	
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree

	void clearTree(QuadtreeNode* &subRoot);
	
	QuadtreeNode* copy(QuadtreeNode* otherRoot);
	
	RGBAPixel getPixelHelper(int x, int y, QuadtreeNode* subRoot) const;
	
	void buildTreeHelper(PNG const & source, QuadtreeNode* subRoot, int x, int y,int resolution);
	
	
	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
