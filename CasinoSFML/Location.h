#pragma once
#include "Place.h"

#include <vector>

class Road;

class Location : public Place
{
public:
	enum Type {
		CITY,
		VILLAGE,
		EMPTY
	};

	//  test
	int color;

	Location();
	~Location();

	// Menage sourrondings 
	bool addRoad(Road* _road);
	std::vector<Road*>::iterator getRoads();

private:
	std::vector<Road*> arrRoads;
};

