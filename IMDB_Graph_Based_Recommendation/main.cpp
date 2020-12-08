#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include "filmGraph.h"
//#include "filereader.h"
using namespace std;

void read_Meta(unordered_map<int, string>& filmCollection, unordered_map<int, vector<int>>& genreCollection);
void read_Keywords(unordered_map<int, vector<int>> keywordCollection);

int main()
{
    clock_t time_req;

    cout << "Welcome to the Supreme Movie Search!" << endl << endl;

    // Graph data
	unordered_map<int, string> filmCollection;
	unordered_map<int, vector<int>> genreCollection;
    unordered_map<int, vector<int>> keywordCollection;

    // read data from files
	read_Meta(filmCollection, genreCollection);
    read_Keywords(keywordCollection);

    // create graph
    filmGraph h(filmCollection, genreCollection, keywordCollection);


    string movie;
    cout << "Enter the name of the movie that you want recommendations for: ";
    cin >> movie;

    int option = 1;
    while (movie != "0") {




        // start time
        time_req = clock();


        // STUFF TO TIME HERE


        // end time
        time_req = clock() - time_req;
        // calculate and print out in seconds
        cout << "Reading files took " << (float)time_req / CLOCKS_PER_SEC << " seconds to calculate" << endl;

    }

	return 0;
}



void read_Meta(unordered_map<int, string>& filmCollection, unordered_map<int, vector<int>>& genreCollection) {//parameters expected to be empty
    ifstream infs("movies_metadata.csv");

    if (infs.is_open()) {
        string throwaway;
        getline(infs, throwaway);

        while (infs.good()) {
            string first;
            getline(infs, first, ',');
            int ID = stoi(first);

            string info;
            getline(infs, info, ','); //title
            filmCollection[ID] = info;//add title to map
            info = "";//clear info

            string buffer;
            getline(infs, buffer);
            stringstream linestream(buffer);
            
            while (linestream.good()) {
                if (buffer == "[]") {
                    break;
                }
                //genres
                string throwaway;
                getline(linestream, throwaway, ':');
                //use integer between colon and comma
                getline(linestream, info, ',');
                // add to vector in map
                genreCollection[ID].push_back(stoi(info));
                info = "";//clear string just in case
                //find next comma(separating keywords) throwaway
                getline(linestream, throwaway, ',');

            }
            
            linestream.clear();
        }
    }

    infs.close();
}

void read_Keywords(unordered_map<int, vector<int>> keywordCollection) {//parameter is expected to be empty map to fill
    ifstream infs("keywords.csv");

    if (infs.is_open()) {
        string throwaway;
        getline(infs, throwaway);

        while (infs.good()) {
            string first;
            getline(infs, first, ',');
            int ID = stoi(first);//gets first entry of each line to store in ID

            string buffer;//get rest of line and then parse that
            getline(infs, buffer);

            stringstream linestream(buffer);//create stream from buffer string that holds rest of line
            while (linestream.good()) {//loop to read a line
                if (buffer == "[]") {//empty keywords
                    break;
                }
                string info;
                //throwaway up to colon
                getline(linestream, throwaway, ':');
                //use integer between colon and comma
                getline(linestream, info, ',');
                // add to vector in map
                keywordCollection[ID].push_back(stoi(info));
                info = "";//clear string just in case
                //find next comma(separating keywords) throwaway
                getline(linestream, throwaway, ',');

            }
            linestream.clear();
        }
    }

    infs.close();
}
