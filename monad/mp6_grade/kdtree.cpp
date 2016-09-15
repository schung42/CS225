/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] == second[curDim])
    {
        if(first < second)
        {
            return true;
        }
       // else return false;
    }

    if(first[curDim] < second[curDim])
    {
        return true;
    }
    return false;
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
    int current = shouldReplaceHelper(currentBest, target);
    int potentialDist = shouldReplaceHelper(potential, target);

    //if the distance between the current closest and potential distance is the same,
    if(current == potentialDist)
    {
        //if the currentBest is not the best point, return true
        if(currentBest > potential)
        {
            return true;
        }
        else return false;
    }
    else if(current < potentialDist)
    {
        return false;
    }
    else return true;
    
}

template<int Dim>
int KDTree<Dim>::shouldReplaceHelper(const Point<Dim> & target1, const Point<Dim> & target2) const
{
    int euclidDistance = 0;

    for(int i = 0; i< Dim; i++)
    {
        euclidDistance = euclidDistance + (target1[i]-target2[i])*(target1[i]-target2[i]);
    }

    return euclidDistance;
}
template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
    points = newPoints;
    if(points.empty())
    {
        return;
    }
    else if(!points.empty())
    {
        createKDTree(0, points.size()-1, 0);
    }

}

template <int Dim>
void KDTree<Dim>::createKDTree(int left, int right, int size)
{
    int median = floor((left + right)/2);

    if(left == right)
    {
        return;
    }

    choose(left, right, size, median);

    //build the left tree
    if(left < median)
    {
        createKDTree(left, median-1,(size+1)%Dim);
    }
    //right subtree
    if(right>median)
    {
        createKDTree(median+1, right, (size+1)%Dim);
    }
}

template<int Dim>
void KDTree<Dim>::choose(int left, int right, int size, int median)
{
    bool loop = true;

    if(right == left)
    {
        loop = false;
    }

    while(loop)
    {
        int curr = partitionKDTree(left, right, size, median);
        if(median > curr)
        {
            left = curr +1;
        }

        else if(median <curr)
        {
            right = curr -1;
        }
        else return;
    }
}

template<int Dim>
int KDTree<Dim>::partitionKDTree(int left, int right, int size, int median)
{
    int retVal = left;
    Point<Dim> tempTree = points[median];

    swap(median, right);

    while(left<right)
    {
        if(smallerDimVal(points[left], tempTree, size) || points[left] == tempTree)
        {
            swap(left, retVal);
            retVal++;
        }
        left++;
    }
    swap(right, retVal);
    return retVal;
}

template<int Dim>
void KDTree<Dim>::swap(int swap1, int swap2)
{
    Point<Dim> temp = points[swap1];
    points[swap1] = points[swap2];
    points[swap2] = temp;
}


template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */

   Point<Dim> retVal;

   retVal = FindNearestNeighborHelp(0, points.size()-1, 0, query);
   
   return retVal;
}

template<int Dim>
Point<Dim> KDTree<Dim>::FindNearestNeighborHelp(int left, int right, int level, Point<Dim> targetPoint) const
{
    int median = floor((left+right)/2);
    
    Point<Dim> midPoint = points[median];

    Point<Dim> currBest = points[median]; //INITIALIZE TO POINTS[MEDIAN], NOT SURE IF I CAN DO THIS BLABH LABH ABLAKBHAKBHAKHBAB

    Point<Dim> temp = points[median];


    //check for leaf node
    if(right <= left)
    {
        return points[left];
    }

    if(smallerDimVal(targetPoint, midPoint, level%Dim))
    {
        //traverse down tree setting the new largest to median-1, and increasing our level by one because we're moving down the tree
        currBest = FindNearestNeighborHelp(left, median-1, level+1, targetPoint);
    }
    else
    {
        //same thing as before except this time we're moving down the right subtree,setting left to one more than median
        currBest = FindNearestNeighborHelp(median+1, right, level+1, targetPoint);
    }

    //check parents (medians)
    if(shouldReplace(targetPoint, currBest, points[median]))
    {
        currBest = points[median];
    }

    //time to calculate radius of currBest to our target so we can compare if its distance is better than the targets distance to splitting plane
    int rad = shouldReplaceHelper(targetPoint, currBest);

    int splitPlaneDist = (currBest[level%Dim] - midPoint[level%Dim])*(currBest[level%Dim] - midPoint[level%Dim]);

    //this compares the distance between target and current best and target and the splitting plane.
    //we repeat what we did up above because we're doing this for the other side of the tree :)
    if(splitPlaneDist <= rad)
    {
        if(smallerDimVal(targetPoint, midPoint, level%Dim))
            temp = FindNearestNeighborHelp(median + 1, right, level+1, targetPoint);
        else
            temp = FindNearestNeighborHelp(left, median -1, level +1, targetPoint);
    }

       if(shouldReplace(targetPoint, currBest, temp))
        {
        //if potential (temp) is a better point relative to targetPoint, then replace currBest with the point we found in the other subtree
        currBest = temp;
        }

 

    return currBest;
}

