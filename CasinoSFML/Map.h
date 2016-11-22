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
		
	Map(int _width, int _height, Style _style, sf::RenderWindow* _window);
	Map( sf::RenderWindow* _window );

	~Map();

	void			draw(sf::RenderWindow & _window);

	sf::Vector2i	getNeighborTile( bool & _status, sf::Vector2i _sourceTile, int _number );
	
	std::vector<std::unique_ptr<Road>> Roads;

public:
	void	acceptDiceThrow( int _dicesum);

private:
	// Default map size
	static const int MAP_EDGE = 5;
	
	int width;
	int height;

	Style style;

	// Render
	sf::RenderWindow* renderWindow;
	void ComputeRender();

	// Acces tile
	Tile* getTile(sf::Vector2i _vector);
	Tile* getTile(int _x, int _y);

	// All tiles
	std::vector< std::vector<std::unique_ptr<Tile>> > tiles;	// All tiles []
	
	std::vector< Tile* > inGameTiles;					// Tiles used in game
	std::vector< std::unique_ptr<Location>> Locations;	// All locations

	/* Circle-style map deploy -- 19 tiles (5x5) */
	void setupCircleMap();
	void SpawnAtTile( Tile* currTile, int i, int j);
};

