#pragma once
#include "Place.h"

#include "Road.h"

class Location : public Place
{
public:
	enum Type {
		CITY,
		VILLAGE,
		EMPTY
	};

	Location();
	~Location();

	// Menage sourrondings 
	bool addRoad(Road* _road);
	std::vector<Road*>::iterator getRoads();

private:
	std::vector<Road*> arrRoads;
};

