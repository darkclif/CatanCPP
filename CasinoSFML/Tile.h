#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "Location.h"
#include "Road.h"
#include "ResourceManager.h"
#include "resources/Textures.h"
#include "Place.h"

class Tile : public Place
{
public:
	// Type of tiles
	enum TileType : int {
		WOOD,
		SHEEP,
		CLAY,
		IRON,
		WHEAT,		
		DESERT,	

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
	sf::Texture& getDiceNumberTexture();

	void draw( sf::RenderWindow & _window );

	// Access soroundings 
	bool addRoad(Road* _road, int _number);
	Road* getRoad(int _number);

	bool addLocation(Location* _location, int _number);
	Location* getLocation(int _number);
	
	// For initialize circle-style map
	int getInitJump();
	void setInitJump( int _jump );

private:
	TileType type;							// Type of resource
	unsigned int diceNumber;				// Number on dices to activate

	// For initialize circle-style map
	int initJump;							// Distance from center of map + 1

	Location* arrLocations[6];	// Cities/villages
	Road* arrRoads[6];			// Roads

	// Tile::Type to Texture::Name
	static const Catan::Textures::Name arrTileToTexture[TileType::__ENUM_SIZE];
	static const Catan::Textures::Name arrDiceToTexture[11];
};


