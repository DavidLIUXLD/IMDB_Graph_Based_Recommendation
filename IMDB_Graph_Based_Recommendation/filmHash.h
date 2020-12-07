#include "film.h"
#pragma once 
class filmHash
{
public:
	size_t operator ()(const film& f) const
	{
		return f.ID;
	}
};


