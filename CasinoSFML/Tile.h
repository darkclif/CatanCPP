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

	bool isThief();
	void setThief(bool _thief);

	TileType getType();				
	void setType(TileType _type); 

	int getDiceNumber();
	void setDiceNumber(int _number);

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
	TileType type;				// Type of resource
	unsigned int diceNumber;	// Number on dices to activate
	bool thief;					// Is thief on this tile

	// For initialize circle-style map
	int initJump;

	Location* arrLocations[6];
	Road* arrRoads[6];

	// Tile::Type to Texture::Name converter
	static const Catan::Textures::Name arrTileToTexture[TileType::__ENUM_SIZE];
	static const Catan::Textures::Name arrDiceToTexture[11];
};


