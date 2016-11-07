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

	// Initialize circle-style map 
	// _x, _y  - center
	// _radius - radius of map
	void CircleMapInit(int _radius, int _x, int _y);
	
	~Map();
private:
	// Default map size
	static const int MAP_WIDTH = 5;
	static const int MAP_HEIGHT = 5;

	int width;
	int height;

	std::vector<std::vector<Tile>> tiles;
};

