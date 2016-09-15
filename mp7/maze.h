#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "dsets.h"
#include <map>
#include <queue>
#include <stack>
#include "png.h"
#include <iostream>
#include <time.h>

using namespace std;

class SquareMaze
{
	public:

		//No-parameter constructor. 
		SquareMaze();

		//Makes a new SquareMaze of the given height and width. 
		void makeMaze(int width, int height);

		//This uses your representation of the maze to determine whether it 
		//is possible to travel in the given direction from the square at coordinates (x,y). 
		bool canTravel(int x, int y, int dir) const;

		//Sets whether or not the specified wall exists. 
		void setWall(int x, int y, int dir, bool exists);

		//Solves this SquareMaze. 
		vector <int> solveMaze();

		//Draws the maze without the solution. 
		PNG* drawMaze() const;

		//This function calls drawMaze, then solveMaze; it modifies the 
		//PNG from drawMaze to show the solution vector and the exit. 
		PNG* drawMazeWithSolution();


	private:

		int mazeWidth;

		int mazeHeight;

		int size;

		DisjointSets cell;

		vector< vector< vector<bool> > > walls;

		vector< vector<int> > potentialPaths;

		vector< int > sol;

		vector< pair< pair<int, int>, int> > Box;

		vector <bool> isRightWall;

		vector <bool> isBotWall;

		int CellIndex(int x, int y) const;

		void solveMazeHelper(int x, int y, vector<int> paths);




	




};
#endif