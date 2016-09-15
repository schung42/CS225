#include <iostream>

using namespace std

int main{
	int v;
	int * w;
	v = 10;
	w = v;
	*w = 8;
	cout << v << endl;
}
