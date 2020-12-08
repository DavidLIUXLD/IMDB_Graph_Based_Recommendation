#include <iostream>
#include <iomanip>
#include <chrono> 
#include "filmGraph.h"
using namespace std;


int main()
{
	clock_t time_req;

	// start time
	time_req = clock();


	// STUFF TO TIME HERE


	// end time
	time_req = clock() - time_req;
	// how to calculate in seconds
	cout << "Recommendations took " << (float)time_req / CLOCKS_PER_SEC << " seconds to calculate" << endl;

	return 0;
}
