#pragma once

#include <vector>
#include "Tile.h"

#include <SFML/Graphics.hpp>
#include <memory>

// Class to store map and all tiles
class Map
{
public:
	enum Style {
		CIRCLE
	};
	
	// Render 
	void Show(sf::RenderWindow & _window, float _x, float _y);

	// Construct map with given dimensions
	Map(int _width, int _height, Style _style);
	Map();
	
	// Return coords of hex adjoined to given hex
	//  _status		- false if there is no specified neighbor, true otherwise
	//  _sourceTile - origin tile
	//	_number		- number of wanted tile; 1- top-right, 2 - right ... (clockwise)
	sf::Vector2i getNeighborTile( bool & _status, sf::Vector2i _sourceTile, int _number );

	~Map();
private:
	// Default map size
	// Change carefuly, some values may be hardcoded!
	static const int MAP_WIDTH = 5;
	static const int MAP_HEIGHT = 5;

	int width;
	int height;
	Style style;

	// Acces tile
	Tile* getTile(sf::Vector2i _vector);
	Tile* getTile(int _x, int _y);

	// All tiles
	std::vector< std::vector<Tile> > tiles;
	
	std::vector< Tile* > inGameTiles;					// Tiles used in game
	std::vector< std::unique_ptr<Road>> Roads;			// All roads
	std::vector< std::unique_ptr<Location>> Locations;	// All locations

	// Prepare map to play
	void setupMap( Style _style );

	/* Circle-style map deploy -- 19 tiles (5x5) */
	void setupCircleMap();
};

