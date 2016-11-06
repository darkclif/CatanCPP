#include "Map.h"



Map::Map(): width( Map::MAP_WIDTH ), height(Map::MAP_HEIGHT)
{
	// Prepare tiles
	this->tiles.resize(height);
	for (int i = 0; i < height; i++) {
		tiles[i].resize(width);
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height; j++) {
			tiles[i][j] = Tile();
		}
	}

}

void Map::Show(sf::Window _window)
{

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height; j++) {
			tiles[i][j].getType();

		}
	}

}

Map::Map(int _width, int _height) : width{_width}, height{ _height }
{

}

Map::~Map()
{
}
