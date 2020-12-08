#include <iostream>
#include <iomanip>
#include <chrono>
#include "filmGraph.h"
#include "filereader.h"
using namespace std;


int main()
{
	clock_t time_req;

	// start time
	time_req = clock();

	// STUFF TO TIME HERE
	unordered_map<int, string> filmCollection;
	unordered_map<int, vector<int>> genreCollection;
	read_Meta(filmCollection, genreCollection);

	// end time
	time_req = clock() - time_req;
	// how to calculate in seconds
	cout << "Reaading files took " << (float)time_req / CLOCKS_PER_SEC << " seconds to calculate" << endl;

	return 0;
}
