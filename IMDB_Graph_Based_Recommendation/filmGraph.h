#pragma once
#include "film.h"
#include "filmEdge.h"
#include "filmEdge.h"
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
using namespace std;

class filmGraph
{

private: 
	//adjacentList for film nodes
	unordered_map<int, vector<filmEdge>> adjacentList;
	unordered_map<int, film> films;

	//return the inverse of jaccard similarity between two vectors,
	//if the jaccard similiarity between given vectors is zero, return zero
	double similarityScore(vector<int> listA, vector<int> listB)
	{
		unordered_set<int> uniqueItem;
		int commonItem = 0;
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

	int findMin(unordered_map<int, double> distances, unordered_set<int> toVisit) {
		double minDis = (double)INT_MAX;
		int minItem = -1;
		for (auto itr : toVisit) {
			if (distances.at(itr) < minDis) {
				minDis = distances.at(itr);
				minItem = itr;
			}
		}
		return minItem;
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
			film movie(filmCollection.at(i), genreCollection.at(i), keywordCollection.at(i));
			films.insert(make_pair(i,movie));
			storage.push_back(movie);
		}
		for (int i = 0; i <= storage.size() - 1; i ++)
		{
			for (int j = i + 1; j <= storage.size() - 1; j ++)
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
					if (adjacentList.count(i))
					{
						vector<filmEdge> similarFilms;
						adjacentList.insert(make_pair(i, similarFilms));
					}
					if (adjacentList.count((j)))
					{
						vector<filmEdge> similarFilms;
						adjacentList.insert(make_pair(j, similarFilms));
					}
					adjacentList.at(i).push_back(edge);
					adjacentList.at(j).push_back(edge);
				}
			}
		}
	}

	vector<double> dijkstras(int sourceID)
	{
		vector<double> distances(films.size(), (double)INT_MAX);
		unordered_map<int, double> minDistances;
		unordered_set<int> processed;
		unordered_set<int> toProcess;
		distances.at(sourceID) = 0;
		for (int i = 0; i <= films.size() - 1; i++) {
			if (i == sourceID) {
				minDistances.insert(make_pair(i, 0));
			}
			else {
				minDistances.insert(make_pair(i, (double)INT_MAX));
			}
		}
		toProcess.insert(sourceID);
		while (!toProcess.empty()) {
			int currentFilm = findMin(minDistances, toProcess);
			toProcess.erase(currentFilm);
			processed.insert(currentFilm);
			vector<filmEdge> relatedFilms = adjacentList.at(currentFilm);
			for (auto itr : relatedFilms) {
				int item = itr.getOtherFilm(currentFilm);
				int newDis = minDistances.at(currentFilm) + itr.similarityScore;
				int oldDis = minDistances.at(item);
				if (!processed.count(item) and newDis < oldDis) {
					minDistances.at(item) = newDis;
					if (oldDis == (double)INT_MAX) {
						toProcess.insert(item);
					}
				}
			}
		}
		for (auto itr : minDistances) {
			distances.at(itr.first) = itr.second;
		}
		return distances;
	}
};

