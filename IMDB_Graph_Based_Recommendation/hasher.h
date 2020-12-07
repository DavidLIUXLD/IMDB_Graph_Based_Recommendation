#pragma once
#include "film.h"
class hasher
{
	size_t operator ()(const film& f) const
	{
		return f.ID;
	}
};

