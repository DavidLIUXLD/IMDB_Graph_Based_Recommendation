#pragma once
#include "filmEdge.h"
using namespace std;
class edgeHash
{
public:
	size_t operator()(const filmEdge& edge)
	{

		return hash<string>()(to_string(edge.fromID) + to_string(edge.toID));
	}
};

