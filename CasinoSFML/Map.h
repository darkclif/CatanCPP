#pragma once

#include <vector>
#include "Tile.h"
#include <SFML/Graphics.hpp>

// Class to store map and all tiles
class Map
{
public:
	// Render 
	void Show( sf::Window _window );


	// Construct map with given dimensions
	Map(int _width, int _height);

	Map();
	
	~Map();
private:
	// Default map size
	static const int MAP_WIDTH = 5;
	static const int MAP_HEIGHT = 5;

	int width;
	int height;

	std::vector<std::vector<Tile>> tiles;
};

