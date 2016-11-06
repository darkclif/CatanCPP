#pragma once

// Class to store map and all tiles

class Map
{
public:

	// Default map size
	static const int MAP_WIDTH = 5;
	static const int MAP_HEIGHT = 5;


	Map();

	// Construct map with given dimensions
	Map( int _width, int _height );

	~Map();
};

