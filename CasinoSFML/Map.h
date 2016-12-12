#pragma once
#include <vector>
#include <memory>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "SelectableMapItem.h"
#include "ResourceManager.h"
#include "Console.h"

class PlayerGUI;

class Map
{
public:
	enum SelectionMode {
		NONE,
		SELECT_ROAD,
		SELECT_CITY,
		SELECT_VILLAGE,
		SELECT_TILE,
		_SIZE
	};

	Map( sf::RenderWindow* _window );
	~Map();

	void			Draw(sf::RenderWindow & _window);
	void			HandleEvent(sf::Event _event);
	void			Update(sf::Time _dt);

	sf::Vector2i	getNeighborTile( bool & _status, sf::Vector2i _sourceTile, int _number );
	
	void			requestSelection(SelectionMode _mode, PlayerGUI* _playerGUI);
	void			cancelSelection();

	friend class PlayerGUI;
public:
	void			acceptDiceThrow( int _dicesum);

private:
	void			sendSelection(SelectableMapItem* _item);
	PlayerGUI*		playerGUI;

	SelectionMode	selectionMode;
	SelectableMapItem* highlightedItem;

	void			checkItemsForClick( sf::Event _event );
	void			checkItemsForHighlight(sf::Event _event);

	// Default map size
	static const int MAP_EDGE = 5;
	int width;
	int height;

	sf::RenderWindow* renderWindow;
	void ComputeRender();

	Tile* getTile(sf::Vector2i _vector);
	Tile* getTile(int _x, int _y);

	// All tiles
	std::vector< std::vector<std::unique_ptr<Tile>> > tiles;	// All tiles []

	std::vector< Tile* >					inGameTiles;					
	std::vector<std::unique_ptr<Location>> Locations;
	std::vector<std::unique_ptr<Road>>		Roads;

	/* Circle-style map deploy -- 19 tiles (5x5) */
	void setupCircleMap();
	void SpawnAtTile( Tile* currTile, int i, int j);
};

