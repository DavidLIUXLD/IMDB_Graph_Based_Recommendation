#pragma once
class filmEdge
{
public:
	int fromID;
	int toID;
	double similarityScore;

	filmEdge()
	{
		this->similarityScore = -1;
	}

	filmEdge(int fromID, int toID, double similiarityScore)
	{
		this->fromID = fromID;
		this->toID = toID;
		similarityScore = similarityScore;
	}

	int getOtherFilm(int ID)
	{
		if (fromID == ID) {
			return toID;
		}
		return fromID;
	}

};

