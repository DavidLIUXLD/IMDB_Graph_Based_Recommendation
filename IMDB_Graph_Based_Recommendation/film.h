#pragma once
#include<string>
#include<vector>
using namespace std;
class film
{
private:
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
		title = "";
	};

	//constructor with parameter
	film(string title, vector<int> genres, vector<int> keywords)
	{	
		this->title = title;
		this->genres = genres;
		this->keywords = keywords;
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



