#pragma once
#include<string>
#include<vector>
using namespace std;
class film
{
private:
	int ID;
	//film title
	string title;
	//collection of genre ID related to the film
	vector<int> genres;
	//collection of keyword ID related to the film
	vector<int> keywords;
public:
	//public ID for Hashing
	//default constructor
	film() 
	{	
		ID = -1;
		title = "";
	};

	//constructor with parameter
	film(int ID, string title, vector<int> genres, vector<int> keywords)
	{	
		this->ID = ID;
		this->title = title;
		this->genres = genres;
		this->keywords = keywords;
	}

	int getID()
	{
		return ID;
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
};
