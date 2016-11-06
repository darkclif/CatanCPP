#pragma once
#include "Place.h"

#include <vector>
#include "Location.h"

class Road : public Place
{
public:
	Road();
	~Road();

	// Menage sourrondings 
	bool addLocation(Location* _location);
	std::vector<Location*>::iterator getLocations();

private:
	std::vector<Location*> arrLocations;
};

