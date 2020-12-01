#pragma once
#include "film.h"
#include "filmEdge.h"
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;
class filmGraph
{

private: 
	unordered_map<film, unordered_set<filmEdge>> adjacentList;
	vector<film> films;
	vector<filmEdge> filmEdges;

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
	filmGraph(unordered_map<int,string> filmCollection, unordered_map<int, vector<int>> genreCollection,
			  unordered_map<int,vector<int>> keywordCollection) 
	{
		for (int i = 0; i <= filmCollection.size(); i++) 
		{
			film movie(i, filmCollection.at(i), genreCollection.at(i), keywordCollection.at(i));
			films.push_back(movie);
		}
		for (int i = 0; i <= films.size(); i ++)
		{
			for (int j = i + 1; j <= films.size(); j ++)
			{
				float similarityScore;
				int commonGenre = 0;
				vector<int> genresOne = films.at(i).getGenres();
				vector<int> genresTwo = films.at(j).getGenres();
				similarityScore = 10 * this->similarityScore(genresOne, genresTwo);
				if (similarityScore != 0)
				{
					vector<int> keywordOne = films.at(i).getKeywords();
					vector<int> keywordTwo = films.at(j).getKeywords();
					similarityScore += 5 * this->similarityScore(keywordOne, keywordTwo);
					filmEdge edge(films.at(i), films.at(j), similarityScore);
					if (adjacentList.count(films.at(i)))
					{
						unordered_set<filmEdge> similarFilms;
						adjacentList.insert(make_pair(films.at(i), similarFilms));
					}
					if (adjacentList.count(films.at(j)))
					{
						unordered_set<filmEdge> similarFilms;
						adjacentList.insert(make_pair(films.at(j), similarFilms));
					}
					adjacentList.at(films.at(i)).insert(edge);
					adjacentList.at(films.at(j)).insert(edge);
					filmEdges.push_back(edge);
				}
			}
		}
	}


	
};

