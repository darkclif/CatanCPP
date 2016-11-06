#include "Tile.h"



Tile::Tile()
{
}


Tile::~Tile()
{
}

std::vector<Location*>::iterator Tile::getLocations()
{
	return this->arrLocations.begin();
}

std::vector<Road*>::iterator Tile::getRoadds()
{
	return this->arrRoads.begin();
}
