#pragma once

#include <vector>
#include <string>

#include "Location.h"
#include "Road.h"

class Tile
{
public:
	// Type of tiles
	enum TileType : int {
		WOOD,		// Las
		SHEEP,		// Owce
		CLAY,		// Glina
		IRON,		// �elazo
		WHEAT,		// Zbo�e
		DESERT,		// Pustynia

		BLANK,		// Do wylosowania
		NOT_USED,	// Poza gra

		__ENUM_SIZE
	};

	Tile(TileType _type, unsigned int _number);
	Tile();

	~Tile();

	// Get/set type of hex
	TileType getType();				
	void setType(TileType _type); 
	
	// Get name of tile texture 
	std::string getTextureName(); 

	// Access sourondings 
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


static const std::string arrTileToTexture[Tile::TileType::__ENUM_SIZE] = {
	"tile_texture_wood",	// WOOD
	"tile_texture_sheep",	// SHEEP		
	"tile_texture_clay",	// CLAY		
	"tile_texture_iron",	// IRON		
	"tile_texture_wheat",	// WHEAT		
	"tile_texture_desert",	// DESERT		
	"tile_texture_blank",	// BLANK		
	"tile_texture_blank",	// NOT_USED	
};

