//
// Created by Dillan Maraj on 12/4/20.
//
#pragma once
#include filereader.h
#include filmGraph.h
#include <ifstream>
#include <sstream>
using namespace std;

void read_Meta(unordered_map<int,string> filmCollection, unordered_map<int, vector<int>> genreCollection){//parameters expected to be empty
    ifstream infs("movies_metadata.csv");

    if(infs.is_open()){
        string throwaway;
        getline(infs, throwaway);

        while(infs.good()){
            string first;
            getline(infs,first,',')
            int ID = stoi(first);

            string buffer;
            getline(infs,buffer);
            stringstream linestream(buffer);
            while(linestream.good()){
                if(buffer=="[]"){
                    break;
                }
                string info;
                getline(linestream,info,','); //title
                filmCollection[ID]=info;//add title to map
                info = "";//clear info

                //genres

            }
        }
    }

    infs.close();
}

void read_Keywords(unordered_map<int,vector<int>> keywordCollection){//parameter is expected to be empty map to fill
    ifstream infs("keywords.csv");

    if(infs.is_open()){
        string throwaway;
        getline(infs, throwaway);

        while(infs.good()){
            string first;
            getline(infs,first,',');
            int ID = stoi(first);//gets first entry of each line to store in ID

            string buffer;//get rest of line and then parse that
            getline(infs, buffer);

            stringstream linestream(buffer);//create stream from buffer string that holds rest of line
            while(linestream.good()){//loop to read a line
                if (buffer=="[]"){//empty keywords
                    break;
                }
                string info;
                //throwaway up to colon
                getline(linestream,throwaway, ':' );
                //use integer between colon and comma
                getline(linestream, info, ',')
                // add to vector in map
                keywordCollection[ID].push_back(stoi(info));
                info = "";//clear string just in case
                //find next comma(separating keywords) throwaway
                getline(linestream, throwaway, ',');

            }
            linestream.close();
        }
    }

    infs.close();
}