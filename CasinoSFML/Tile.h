#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "Location.h"
#include "Road.h"
#include "ResourceManager.h"
#include "resources/Textures.h"

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

	// Get/set dice number
	int getDiceNumber();
	void setDiceNumber(int _number);

	// Get name of tile texture 
	sf::Texture& getTexture(); 

	// Access soroundings 
	bool addRoad( Road* _road);
	std::vector<Road*>::iterator getRoadds();

	bool addLocation(Location* _location);
	std::vector<Location*>::iterator getLocations();
	
	// For initialize circle-style map
	int getInitJump();
	void setInitJump( int _jump );

private:
	TileType type;							// Type of resources 
	unsigned int diceNumber;				// Number on dices to activate

	// For initialize circle-style map
	int initJump;							// Distance from center of map + 1

	std::vector<Location*> arrLocations;	// Cities/villages (max: 6)
	std::vector<Road*> arrRoads;			// Roads (max: 6)

	static const Catan::Textures::Name arrTileToTexture[ TileType::__ENUM_SIZE ];
};


