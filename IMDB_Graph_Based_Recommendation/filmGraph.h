#pragma once
#include "film.h"
#include "filmEdge.h"
#include "filmHash.h"
#include "filmEdge.h"
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;

class filmGraph
{

private: 
	//adjacentList for film nodes
	unordered_map<film, vector<filmEdge>, filmHash> adjacentList;
	//collection of all films 
	unordered_set<film, filmHash> films;

	//return the inverse of jaccard similarity between two vectors,
	//if the jaccard similiarity between given vectors is zero, return zero
	float similarityScore(vector<int> listA, vector<int> listB)
	{
		unordered_set<int> uniqueItem;
		int commonItem;
		for (auto itr1 : listA)
		{
			uniqueItem.insert(itr1);
		}
		for (auto itr2 : listB)
		{
			if (uniqueItem.count(itr2))
			{
				commonItem++;
			}
		}
		if (commonItem != 0)
		{
			return 1 / (commonItem / (sizeof(listA) + sizeof(listB) - commonItem));
		}
		return 0;
	}

public:
	//given unordered_map filmCollections mapping film IDs to film titles, unordered_map genreCollection
	//mapping from film IDs to a list of genre IDs, and unordered_map keywordCollection mapping from 
	//film IDs to a list of keyword IDs, construct the filmGraph object
	filmGraph(unordered_map<int,string> filmCollection, unordered_map<int, vector<int>> genreCollection,
			  unordered_map<int,vector<int>> keywordCollection) 
	{
		//temperary collection of films for better iteration access
		vector<film> storage;
		for (int i = 0; i <= filmCollection.size() - 1; i++) 
		{
			film movie(i, filmCollection.at(i), genreCollection.at(i), keywordCollection.at(i));
			films.insert(movie);
			storage.push_back(movie);
		}
		for (int i = 0; i <= films.size() - 1; i ++)
		{
			for (int j = i + 1; j <= films.size() - 1; j ++)
			{	
				//calculate similarityScore based on genres of the film
				float similarityScore;
				vector<int> genresOne = storage.at(i).getGenres();
				vector<int> genresTwo = storage.at(j).getGenres();
				similarityScore = 10 * this->similarityScore(genresOne, genresTwo);
				//two films share some genres, adding edge
				if (similarityScore != 0)
				{
					vector<int> keywordOne = storage.at(i).getKeywords();
					vector<int> keywordTwo = storage.at(j).getKeywords();
					similarityScore += 5 * this->similarityScore(keywordOne, keywordTwo);
					filmEdge edge(i, j, similarityScore);
					if (adjacentList.count(storage.at(i)))
					{
						vector<filmEdge> similarFilms;
						adjacentList.insert(make_pair(storage.at(i), similarFilms));
					}
					if (adjacentList.count(storage.at(j)))
					{
						vector<filmEdge> similarFilms;
						adjacentList.insert(make_pair(storage.at(j), similarFilms));
					}
					adjacentList.at(storage.at(i)).push_back(edge);
					adjacentList.at(storage.at(j)).push_back(edge);
				}
			}
		}
	}
	
	
		bool findConnection(vector<filmEdge> &edges, filmEdge &find)
	{
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges.at(i) == find)
				return true;
		}
		return false;
	}

	void dijkstras(film source)
	{
		int* d;
		int* p;
		unordered_set<film, filmHash> S;
		unordered_set<film, filmHash> VS = films;

		for (auto iter = VS.begin(); iter != VS.end(); iter++)
		{
			if (found)
			d[i] = INT_MAX;
			p[i] = -1;
		}

		
		while (!VS.empty())
		{
			for(int i = 0; i < )

		}

	}
	
};

