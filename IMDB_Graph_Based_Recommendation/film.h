#include<string>
using namespace std;
class film
{
private:
	int ID;
	string title;
	string genre;
	int distance;


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
};

