#include "maze.h"

#define RIGHT 0
#define BOTTOM 1
#define LEFT 2
#define UP 3


SquareMaze::SquareMaze()
{
    mazeWidth = 0;
    mazeHeight = 0;
    size = 0;
    cell = DisjointSets();
}


void SquareMaze::makeMaze(int width,int height) 
{
	size = width * height;
	mazeWidth = width;
	mazeHeight = height;

	//make it the width then make each of those slots the height, then 
	walls.resize(width);

	for(int i = 0; i< width; i++)
	{
		walls[i].resize(height);

		for(int j = 0; j< height; j++)
		{
			walls[i][j].resize(2);
		}
	}

	srand(time(NULL));

	//disjointset to rep cells
	cell.addelements(size);

	//walls are true
	for(int i = 0; i< width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			for(int k = 0; k < 2 ;k++)
			{
				walls[i][j][k] = true;
			}
		}
	}

	// need this to keep track of disjoint set
	int join = width*height;

	// don't need this anymore
	//walls are true ^^^^^^^^
	isRightWall = vector<bool> (size, true);
	isBotWall = vector<bool> (size, true);


	//remove walls randomly 
	while(join > 1)
	{
		int randx = rand()% width;
		int randy = rand()% height;
		int dir =  rand()% 2;
		int ID = CellIndex(randx, randy);

		if(dir)
		{
			if(ID + width >= size)
			{
				continue;
			}

			if(cell.find(ID) == cell.find(ID +width))
			{
				continue;
			}

			cell.setunion(ID, ID+width);

			walls[randx][randy][dir] = false;

			join--;


		}
		else
		{
			if(((ID +1) % width) == 0)
				continue;

			if(cell.find(ID) == cell.find(ID +1))
				continue;

			cell.setunion(ID, ID+1);

			walls[randx][randy][dir] = false;

			join--;

		}
}


}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
	//check if values are valid
	if(x < 0 || y<0 || x > mazeWidth || y >mazeHeight)
	{
		return false;
	}
	//check if you're at the edges of the maze
	if( (x == 0 && dir == LEFT) || (y==0 && dir == UP) || 
		(x ==mazeWidth-1 && dir == RIGHT) || (y == mazeHeight-1 && dir == BOTTOM) )
	{
		return false;
	}

	if(dir == RIGHT)
	{
		return !( isRightWall[ CellIndex(x,y) ] );
	}

	else if(dir == BOTTOM)
	{
		return !( isBotWall[ CellIndex(x,y) ] );
	}

	else if(dir ==LEFT)
	{
		return !( isRightWall[CellIndex(x-1, y) ] );
	}

	else if(dir == UP)
	{
		return !( isBotWall[CellIndex(x, y-1) ] );
	}

	else return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	walls[x][y][dir] = exists;
}

vector<int>SquareMaze::solveMaze()
{
	potentialPaths.resize(mazeWidth);

	vector<int> empty;
	//create a vector of vectors which is basically seeing with vector is the longest.
	//this longest path is the solution to our maze
	solveMazeHelper(0,0,empty);

	int smallestX = 0;
	sol = potentialPaths[0];

	for(int i = 0; i< mazeWidth; i++)
	{
		if(potentialPaths[i].size() > sol.size())
			sol = potentialPaths[i];
	}

return sol;



}

PNG * SquareMaze::drawMaze() const
{
	PNG* retImage = new PNG(mazeWidth*10+1, mazeHeight*10+1);

	for(int i = 0; i < retImage->width(); i++)
	{
		*(*retImage)(i,0) = RGBAPixel(0,0,0);
	}

	for(int i = 0; i< retImage->height(); i++)
	{
		*(*retImage)(0,i) = RGBAPixel(0,0,0);
	}

	//go through the entire maze
	for(int x = 0; x < mazeWidth; x++)
		for(int y = 0; y < mazeHeight; y++)
		{
			if(walls[x][y][0])
				for(int k = 0; k < 10; k++)
					*(*retImage)((x+1)*10, y*10+k) = RGBAPixel(0,0,0);
			if(walls[x][y][1])
				for(int k = 0; k < 10; k++)
					*(*retImage)(x*10+k, (y+1)*10) = RGBAPixel(0,0,0);
		}
return retImage;
}

PNG * SquareMaze::drawMazeWithSolution()
{
	PNG* retVal = drawMaze(); //placeholders
	
	int x = 5;
	int y = 5;

	while(!sol.empty())
	{
		int dir = sol.back();
		sol.pop_back();
		if(dir == 0)
		{
			for(int i = 0; i < 11; i++)
				*(*retVal)(x+i, y) = RGBAPixel(255,0,0);
			x += 10;
		}
		if(dir == 1)
		{
			for(int i = 0; i < 11; i++)
				*(*retVal)(x, y+i) = RGBAPixel(255,0,0);
			y += 10;
		}
		if(dir == 2)
		{
			for(int i = 0; i < 11; i++)
				*(*retVal)(x-10+i, y) = RGBAPixel(255,0,0);
			x -= 10;
		}
		if(dir == 3)
		{	
			for(int i = 0; i < 11; i++)
				*(*retVal)(x, y-10+i) = RGBAPixel(255,0,0);
			y -=10;
		}

	}
	return retVal;
}

int SquareMaze::CellIndex(int x, int y) const
{
	return y * mazeWidth +x;
}

void SquareMaze::solveMazeHelper(int x, int y, vector<int> paths)
{
	if(y == (mazeHeight-1))
	{
		potentialPaths[x] = paths;
	}

	if(canTravel(x,y,0))
	{
		if(paths.empty())
		{
			paths.push_back(0);
			solveMazeHelper(x+1, y, paths);
			paths.pop_back();
		}
		else if (paths.back()!=2)
		{
			paths.push_back(0);
			solveMazeHelper(x+1, y, paths);
			paths.pop_back();
		}
	}

	if(canTravel(x,y,1))
	{
		if(paths.empty())
		{
			paths.push_back(1);
			solveMazeHelper(x, y+1, paths);
			paths.pop_back();
		}

		else if(paths.back()!= 3)
		{
			paths.push_back(1);
			solveMazeHelper(x, y+1, paths);
			paths.pop_back();
		}
	}

	if(canTravel(x,y,2))
	{
		if(paths.empty())
		{
			paths.push_back(2);
			solveMazeHelper(x-1, y, paths);
			paths.pop_back();
		}
		else if(paths.back()!=0)
		{
			paths.push_back(2);
			solveMazeHelper(x-1, y, paths);
			paths.pop_back();
		}
	}

	if(canTravel(x,y,3))
	{
		if(paths.empty())
		{
			paths.push_back(3);
			solveMazeHelper(x, y-1, paths);
			paths.pop_back();
		}

		else if(paths.back()!= 1)
		{
			paths.push_back(3);
			solveMazeHelper(x, y-1, paths);
			paths.pop_back();
		}
	}


}