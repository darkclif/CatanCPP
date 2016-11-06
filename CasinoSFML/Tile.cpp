#include "Tile.h"



Tile::Tile(TileType _type, unsigned int _number) : type{ _type }, number{ _number } {
};

Tile::Tile() : type{ NOT_USED }, number{ 0 } {
}
Tile::~Tile()
{
};

Tile::TileType Tile::getType() {
	return type;
}

bool Tile::addRoad(Road * _road)
{
	for (std::vector<Road*>::iterator it = arrRoads.begin(); it != arrRoads.end(); it++ ) {
		if ( _road == *it ) return false;
	}

	// Only six roads beside the tile
	if (arrLocations.size() == 6)
		throw std::logic_error("Too many unique roads at signle tile!");

	arrRoads.push_back(_road);
	return true;
}

bool Tile::addLocation(Location * _location)
{
	for (std::vector<Location*>::iterator it = arrLocations.begin(); it != arrLocations.end(); it++) {
		if (_location == *it) return false;
	}

	// Only six locations beside the tile
	if (arrLocations.size() == 6)
		throw std::logic_error("Too many unique locations at signle tile!");

	arrLocations.push_back(_location);
	return true;
}

std::vector<Location*>::iterator Tile::getLocations()
{
	return this->arrLocations.begin();
}

std::vector<Road*>::iterator Tile::getRoadds()
{
	return this->arrRoads.begin();
}
