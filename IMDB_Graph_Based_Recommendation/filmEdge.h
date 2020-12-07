#pragma once
#include"film.h"
class filmEdge
{
public:
	int fromID;
	int toID;
	float similarityScore;

	filmEdge()
	{
		this->similarityScore = -1;
	}

	filmEdge(int fromID, int toID, float similiarityScore)
	{
		this->fromID = fromID;
		this->toID = toID;
		similarityScore = similarityScore;
	}

	bool operator< (const filmEdge& other)
	{
		if (this->similarityScore < other.similarityScore) {
			return true;
		}
		return false;
	}

	bool operator> (const filmEdge& other)
	{
		if (this->similarityScore > other.similarityScore) {
			return true;
		}
		return false;
	}

	bool operator== (const filmEdge& other)
	{
		if (this->fromID == other.fromID and this->toID == other.toID) {
			return true;
		}
		return false;
	}
};

