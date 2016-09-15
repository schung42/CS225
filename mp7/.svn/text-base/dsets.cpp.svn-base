#include <vector>
#include "dsets.h"

void DisjointSets::addelements(int num)
{
	int currSize = vec.size();
	
	vec.resize(vec.size() + num);
	
	int i = currSize;

	while(i < vec.size())
	{
		vec[i] =-1;
		i++;
	}
}

int DisjointSets::find(int elem)
{
	if(vec[elem] < 0)
	{
		return elem;
	}
	else
	{
		vec[elem] = find(vec[elem]);
		return vec[elem];
	}
}

void DisjointSets::setunion(int a, int b)
{
	a = find(a);
	b = find(b);

	int currSize = vec[a] + vec[b];

	if(vec[a] <= vec[b])
	{
		vec[b] = a;
		vec[a] = currSize;
	}
	else
	{
		vec[a] = b;
		vec[b] = currSize;
	}
}
