#include "Reducer.h"
#include <iostream>

using namespace std;

// DO NOT MODIFY (except to test different maps)
int main()
{
	ConnectionMap c(4, 3, "data.txt");
	if (backtrack(c, 0))
	{
		cout << "Solved!" << endl;
	}
	else
	{
		cout << "No solution." << endl;
	}

	return 0;
}

