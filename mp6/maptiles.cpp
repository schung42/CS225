/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
	
	//declaration and set up for the mosaic canvas that will be returned
	//sets up vectors for the map and tiles, will go through tree and get colors
	vector<Point<3> > pointColor;
	map<Point<3>, TileImage> pointMap; 
	int count = 0;
	int rows = theSource.getRows();
	int columns = theSource.getColumns();
 	MosaicCanvas *finalImage = new MosaicCanvas(rows, columns);

	//base cases
	if (theSource.getRows() == 0)
		return NULL;
	if (theSource.getColumns() == 0)
		return NULL;
	if (theTiles.empty())
		return NULL;
	//loops through tiles to build the map
	
	while(count < theTiles.size())
	{
		RGBAPixel tiling = theTiles.at(count).getAverageColor();
		Point<3> tileCol(tiling.red, tiling.green, tiling.blue);
		pointMap[tileCol] = theTiles.at(count);
		pointColor.push_back(tileCol);
		count = count+1;
	}
	KDTree<3> colorTree(pointColor); //declares the KDtree
	//loops through tiles again to build the image
	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < columns; y++)
		{
			RGBAPixel imageCol = theSource.getRegionColor(x, y);
			Point<3> point1(imageCol.red, imageCol.green, imageCol.blue);
			Point<3> point2 = colorTree.findNearestNeighbor(point1);
			TileImage tileIm = pointMap[point2];
			finalImage->setTile(x, y, tileIm);
		}
	}
	return finalImage;
}
