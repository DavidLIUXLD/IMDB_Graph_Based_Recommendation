#pragma once
#include "film.h"
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
	unordered_map<string, film> films;

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

	vector<pair<double, int>> merge(vector<pair<double, int>> left, vector<pair<double, int>> right) {
		int leftCount = 0;
		int rightCount = 0;

		vector<pair<double, int>> results;

		bool useLeft;
		for (int i = 0; i < left.size() + right.size(); i++) {
			if (leftCount < left.size()) {
				if (rightCount < right.size()) {
					useLeft = (left[leftCount].first < right[rightCount].first);
				}
				else {
					useLeft = true;
				}
			}
			else {
				useLeft = false;
			}

			if (useLeft) {
				results.push_back(left[leftCount]);
				if (leftCount < left.size()) {
					leftCount++;
				}
			}
			else {
				results.push_back(right[rightCount]);
				if (rightCount < right.size()) {
					rightCount++;
				}
			}
		}
		return results;
	}

	vector<pair<double, int>> mergeSort(vector<pair<double, int>> list) {
		if (list.size() <= 1) {
			return list;
		}
		int len = floor(list.size() / 2);
		vector<pair<double, int>> left(list.begin(), list.begin() + len);
		vector<pair<double, int>> right(list.begin() + len, list.end());

		return merge(mergeSort(left), mergeSort(right));
	}

	vector<pair<double, int>> dijkstras(int sourceID)
	{
		vector<pair<double, int>> distances(films.size());
		unordered_map<int, double> minDistances;
		unordered_set<int> processed;
		unordered_set<int> toProcess;
		distances.at(sourceID) = make_pair(0.0, sourceID);
		for (int i = 0; i <= adjacentList.size() - 1; i++) {
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
			distances.at(itr.first) = make_pair(itr.second, itr.first);
		}
		return distances;
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
		for (auto itr : filmCollection) 
		{	
			int ID = itr.first;
			string title = itr.second;
			film movie(ID, title, genreCollection.at(ID), keywordCollection.at(ID));
			films.insert(make_pair(title,movie));
			storage.push_back(movie);
		}
		for (int i = 0; i <= storage.size() - 1; i ++)
		{
			for (int j = i + 1; j <= storage.size() - 1; j ++)
			{	
				//calculate similarityScore based on genres of the film
				int AID = storage.at(i).getID();
				int BID = storage.at(j).getID();
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
					filmEdge edge(AID, BID, similarityScore);
					if (!adjacentList.count(AID))
					{
						vector<filmEdge> similarFilms;
						adjacentList.insert(make_pair(AID, similarFilms));
					}
					if (!adjacentList.count((BID)))
					{
						vector<filmEdge> similarFilms;
						adjacentList.insert(make_pair(BID, similarFilms));
					}
					adjacentList.at(AID).push_back(edge);
					adjacentList.at(BID).push_back(edge);
				}
			}
		}
	}

	vector<int> recommendation (string title)
	{
		vector<int> recommendation;
		int sourceID = films.at(title).getID();
		vector<pair<double,int>> distances = dijkstras(sourceID);
		sort(distances.begin(), distances.end());
		for (int i = 0; i < 20; i++)
		{
			if (distances.at(i).second != sourceID) {
				recommendation.push_back(distances.at(i).second);
			}
		}
		return recommendation;
	}

	vector<int> recommendationByMerge(string title)
	{
		vector<int> recommendation;
		int sourceID = films.at(title).getID();
		vector<pair<double, int>> distances = dijkstras(sourceID);
		distances =  mergeSort(distances);
		for (int i = 0; i < 20; i++)
		{
			if (distances.at(i).second != sourceID) {
				recommendation.push_back(distances.at(i).second);
			}
		}
		return recommendation;
	}
};
