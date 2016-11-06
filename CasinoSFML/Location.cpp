#include "Location.h"



Location::Location()
{
}


Location::~Location()
{
}

bool Location::addRoad(Road * _road)
{
	for (std::vector<Road*>::iterator it = arrRoads.begin(); it != arrRoads.end(); it++) {
		if (_road == *it) return false;
	}

	// Only two locations beside the road 
	if (arrRoads.size() == 3)
		throw std::logic_error("Too many unique roads at signle road!");

	arrRoads.push_back(_road);
	return true;
}

std::vector<Road*>::iterator Location::getRoads()
{
	return arrRoads.begin();
}
