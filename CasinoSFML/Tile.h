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
		IRON,		// ¯elazo
		WHEAT,		// Zbo¿e
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
	std::vector<Road*>::iterator getRoadds();

	bool addLocation(Location* _location);
	std::vector<Location*>::iterator getLocations();
	
	// For initialize circle-style map
	int getInitJump();
	void setInitJump( int _jump );

private:
	TileType type;							// Type of resources 
	unsigned int number;					// Number on dices to activate

	int initJump;							// Distance from center of map + 1

	std::vector<Location*> arrLocations;	// Cities/villages (max: 6)
	std::vector<Road*> arrRoads;			// Roads (max: 6)
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

