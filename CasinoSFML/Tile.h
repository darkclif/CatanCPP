#pragma once

#include <vector>

#include "Location.h"
#include "Road.h"

class Tile
{
public:
	// Type of tiles
	enum TileType {
		WOOD,		// Las
		SHEEP,		// Owce
		CLAY,		// Glina
		IRON,		// ¯elazo
		WHEAT,		// Zbo¿e
		DESERT,		// Pustynia

		BLANK,		// Do wylosowania
		NOT_USED	// Poza gra
	};

	Tile(TileType _type, int _number) : type{ _type }, number{ _number } {};
	Tile() : type{ NOT_USED }, number{ 0 } {};

	~Tile();

	// Acces sourondings 
	bool addRoad( Road* _road);
	bool addLocation(Location* _location);

	std::vector<Location*>::iterator getLocations();
	std::vector<Road*>::iterator getRoadds();

private:
	TileType type;
	unsigned int number;

	std::vector<Location*> arrLocations;
	std::vector<Road*> arrRoads;
};

