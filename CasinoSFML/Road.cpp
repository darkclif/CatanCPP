#include "Road.h"

Road::Road()
{
}


Road::~Road()
{
}

bool Road::addLocation(Location * _location)
{
	for (std::vector<Location*>::iterator it = arrLocations.begin(); it != arrLocations.end(); it++) {
		if (_location == *it) return false;
	}

	// Only two locations beside the road 
	if (arrLocations.size() == 2)
		throw std::logic_error("Too many unique locations at signle road!");

	arrLocations.push_back(_location);
	return true;
}

std::vector<Location*>::iterator Road::getLocations()
{
	return this->arrLocations.begin();
}
