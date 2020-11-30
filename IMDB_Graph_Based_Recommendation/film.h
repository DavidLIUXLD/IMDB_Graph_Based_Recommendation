#include<string>
using namespace std;
class film
{
private:
	int ID;
	string title;
	string genre;
	float distance;


public:
	film(int ID, string title, string genre)
	{
		this->ID = ID;
		this->title = title;
		this->genre = genre;
	}

	int getID()
	{
		return this->ID;
	}

	string getTitle()
	{
		return this->title;
	}

	string getGenre()
	{
		return this->genre;
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

