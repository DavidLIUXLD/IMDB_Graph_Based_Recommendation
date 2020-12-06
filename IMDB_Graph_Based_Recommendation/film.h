#include<string>
#include<vector>
using namespace std;
class film
{
private:
	//unique ID for the film
	int ID;
	//film title
	string title;
	//collection of genre ID related to the film
	vector<int> genres;
	//collection of keyword ID related to the film
	vector<int> keywords;
	//distance to the starting point reserved exclusively for Dijkstra shortest path algorithm
	float distance;

public:
	//default constructor
	film() 
	{
		ID = -1;
		title = "";
		distance = -1;
	};

	//constructor with parameter
	film(int ID, string title, vector<int> genres, vector<int> keywords)
	{	
		this->ID = ID;
		this->title = title;
		this->genres = genres;
		this->keywords = keywords;
		distance = INT_MAX;
	}
	
	//return the unique ID for the film
	int getID()
	{
		return this->ID;
	}

	//return the title for the film
	string getTitle()
	{
		return this->title;
	}

	//return the collection of genre IDs for the film 
	vector<int> getGenres()
	{
		return this->genres;
	}

	//returb the collection of keyword IDs for the film
	vector<int> getKeywords()
	{
		return this->keywords;
	}

	//return the distance of the film from the starting point in dijkstra
	float getDist() 
	{
		return this->distance;
	}

	//set the 
	void setDist(float distance) 
	{
		this->distance = distance;
	}
	//comparison operator overloading for std::priorityqueue compatability 
	bool operator< (const film& other) 
	{
		if (this->distance < other.distance) {
			return true;
		}
		else if(this->ID < other.ID){
			return true;
		}
		return false;
	}

	bool operator> (const film& other)
	{
		if (this->distance > other.distance) {
			return true;
		}
		else if (this->ID > other.ID) {
			return true;
		}
		return false;
	}

	//equal operator overloading dor std::unordered_set and std::unordered_map compatability
	bool operator== (const film& other)
	{
		if (this->ID == other.ID) {
			return true;
		}
		return false;
	}
};

