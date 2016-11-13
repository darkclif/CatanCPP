#pragma once
#include "Place.h"

#include <vector>
#include <iostream>

class Location;

class Road : public Place
{
public:
	Road();
	~Road();

	// Menage sourrondings - 2 location for each road
	bool addLocation(Location* _location);
	std::vector<Location*>::iterator getLocations();

private:

	std::vector<Location*> arrLocations;
};
