#pragma once

#include <vector>
#include "Tile.h"
#include <SFML/Graphics.hpp>

// Class to store map and all tiles
class Map
{
public:
	// Render 
	void Show(sf::RenderWindow & _window, float _x, float _y);

	// Construct map with given dimensions
	Map(int _width, int _height);
	Map();
	
	// Return coords of hex adjoined to given hex
	//  _status		- false if there is no specified neighbor, true otherwise
	//  _sourceTile - origin tile
	//	_number		- number of wanted tile; 1- top-right, 2 - right ... (clockwise)
	sf::Vector2i getNeighborTile( bool & _status, sf::Vector2i _sourceTile, int _number );

	~Map();
private:
	// Default map size
	static const int MAP_WIDTH = 7;
	static const int MAP_HEIGHT = 7;

	int width;
	int height;

	std::vector<std::vector<Tile>> tiles;
	Tile& getTile(sf::Vector2i _vector);

	// Initialize circle-style map 
	//	_x, _y  - center
	//	_radius - radius of map
	void initCircleMap(int _radius);
};

