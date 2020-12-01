#include<string>
#include<unordered_set>
#include<vector>
using namespace std;
class film
{
private:
	int ID;
	string title;
	vector<int> genres;
	vector<int> keywords;
	float distance;

public:
	film() 
	{
		ID = -1;
		title = "";
		distance = -1;
	};

	film(int ID, string title, vector<int> genres, vector<int> keywords)
	{	
		this->ID = ID;
		this->title = title;
		this->genres = genres;
		this->keywords = keywords;
		distance = INT_MAX;
	}

	int getID()
	{
		return this->ID;
	}

	string getTitle()
	{
		return this->title;
	}

	vector<int> getGenres()
	{
		return this->genres;
	}

	vector<int> getKeywords()
	{
		return this->keywords;
	}

	float getDist() 
	{
		return this->distance;
	}
	
	//comparison operator overloading
	bool operator< (const film& other) 
	{
		return this->distance < other.distance;
	}

	bool operator> (const film& other)
	{
		return this->distance > other.distance;
	}

	bool operator== (const film& other)
	{
		return this->distance == other.distance;
	}
};

