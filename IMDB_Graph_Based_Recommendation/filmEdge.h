#pragma once
#include"film.h"
class filmEdge
{
private:
	film from;
	film to;
	float similarityScore;

public:
	filmEdge()
	{
		this->similarityScore = -1;
	}

	filmEdge(film from, film to, float similiarityScore)
	{
		this->from = from;
		this->to = to;
		similarityScore = similarityScore;
	}
};

