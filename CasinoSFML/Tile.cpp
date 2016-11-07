#include "Tile.h"

#include <iostream>

Tile::Tile(TileType _type, unsigned int _number) : 
	type{ _type }, 
	number{ _number },
	initJump{ 0 } {
};

Tile::Tile() : 
	type{ NOT_USED }, 
	number{ 0 },
	initJump{ 0 } {
}

Tile::~Tile()
{
};

Tile::TileType Tile::getType() {
	return type;
}

void Tile::setType(TileType _type)
{
	type = _type;
}

std::string Tile::getTextureName()
{
	return arrTileToTexture[ (int)(this->type) ];
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

int Tile::getInitJump()
{
	return initJump;
}

void Tile::setInitJump(int _jump)
{
	if (_jump < 0) {
		std::string lError = "Tile::setInitJump: JumpNumber less than 0";
		std::cout << lError << std::endl;
		throw std::logic_error(lError);
	}

	this->initJump = _jump;
}

std::vector<Road*>::iterator Tile::getRoadds()
{
	return this->arrRoads.begin();
}
