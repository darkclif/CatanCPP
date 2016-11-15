#include "Map.h"
#include "ResourceManager.h"

#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdlib>

Map::Map( sf::RenderWindow* _window ) : width(Map::MAP_RADIUS), height(Map::MAP_RADIUS), style(Style::CIRCLE), renderWindow{_window}
{
	// Make a square map
	this->tiles.resize(height);
	for (int i = 0; i < height; i++) {
		tiles[i].resize(width);
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tiles[i][j] = Tile();
		}
	}

	// Prepare map to play
	setupCircleMap();

	// Compute position of tiles, roads and locations to draw 
	ComputeRender();
}

void Map::setupCircleMap() {
	
	//
	// Set TileType::BLANK and TileType::DESERT at center
	//

	// Calculate center of map
	if (!(this->height % 2 || this->width % 2) ) {
		std::cout << "setupCircleMap: Map heigh or width is even - some hexes will remain unused." << std::endl;
	}
	if (this->width != this->height) {
		std::cout << "setupCircleMap: Map heigh and width are not equals - some hexes will remain unused." << std::endl;
	}

	int a = (width < height ? width : height);
	int x = a / 2;
	int y = a / 2;

	int lRadius = std::ceil((float)a / 2.0 );
	
	// Add center tile to queue and start spreading map 
	std::queue<sf::Vector2i> qTileToInit;

	tiles[x][y].setInitJump(1);
	tiles[x][y].setType(Tile::TileType::DESERT);
	qTileToInit.push(sf::Vector2i(x, y));

	while (!qTileToInit.empty()) {
		sf::Vector2i lVector = qTileToInit.front();
		qTileToInit.pop();

		int lJump = getTile(lVector)->getInitJump();

		// Set tile type 
		if (getTile(lVector)->getType() == Tile::TileType::NOT_USED)
			getTile(lVector)->setType(Tile::TileType::BLANK);

		// Add tile to in-game list
		inGameTiles.push_back(getTile(lVector));

		// Search for further tiles if current tile is not map edge
		if (getTile(lVector)->getInitJump() < lRadius) {
			for (int i = 0; i < 6; i++) {
				bool lStatus;
				sf::Vector2i lNgVector = getNeighborTile(lStatus, lVector, i);

				// Add to queue if tile exist and have not been added yet 
				if (lStatus && getTile(lNgVector)->getInitJump() == 0) {
					getTile(lNgVector)->setInitJump(lJump + 1);
					qTileToInit.push(lNgVector);
				}
			}
		}

	}/* while*/

	//
	// Assign tile types and dice numbers to TileType::BLANK
	//

	// Prepare resources to assign
	std::vector<Tile::TileType> tileTypes;

	int tileToShuffleCount = inGameTiles.size() - 1; // All in game tiles (-1) Desert in the middle
	int countBlock = 0;

	int tileToAssignNumbers = tileToShuffleCount;
	int countDesert = 0;

	/*
		If map is not setup in standard 19-tile way insert 
		more tiles in given manner:

			Wo	Sh	Wh	Cl	Ir	De	- Cnt
		s1.	4	4	4	3	3	0	- 18 (if map have 19 tiles insert this block 1 time)
		s2.	2	2	2	1	1	1	- 9
		s3.	1	1	1	0	0	0	- 3
	*/

	// Step 1
	countBlock = tileToShuffleCount / 18;
	for (int i = 0; i < countBlock; i++) {
		Tile::TileType lTiles[] = {
			Tile::TileType::SHEEP, Tile::TileType::SHEEP, Tile::TileType::SHEEP, Tile::TileType::SHEEP,
			Tile::TileType::WOOD, Tile::TileType::WOOD, Tile::TileType::WOOD, Tile::TileType::WOOD,
			Tile::TileType::WHEAT, Tile::TileType::WHEAT, Tile::TileType::WHEAT, Tile::TileType::WHEAT,
			Tile::TileType::IRON, Tile::TileType::IRON, Tile::TileType::IRON,
			Tile::TileType::CLAY, Tile::TileType::CLAY, Tile::TileType::CLAY
		};
		tileTypes.insert( tileTypes.begin(), lTiles, lTiles + 18);
	}
	tileToShuffleCount -= countBlock * 18;

	// Step 2
	countBlock = tileToShuffleCount / 9;
	for (int i = 0; i < countBlock; i++) {
		Tile::TileType lTiles[] = {
			Tile::TileType::SHEEP, Tile::TileType::SHEEP,
			Tile::TileType::WOOD, Tile::TileType::WOOD,
			Tile::TileType::WHEAT, Tile::TileType::WHEAT,
			Tile::TileType::IRON,
			Tile::TileType::CLAY,
			Tile::TileType::DESERT
		};
		tileTypes.insert(tileTypes.begin(), lTiles, lTiles + 9);
		countDesert++;
	}
	tileToShuffleCount -= countBlock * 9;

	// Step 3
	countBlock = tileToShuffleCount / 3;
	for (int i = 0; i < countBlock; i++) {
		Tile::TileType lTiles[] = {
			Tile::TileType::SHEEP,
			Tile::TileType::WOOD, 
			Tile::TileType::WHEAT 
		};
		tileTypes.insert(tileTypes.begin(), lTiles, lTiles + 3);
	}
	tileToShuffleCount -= countBlock * 3;

	// Prepare numbers to assign
	tileToAssignNumbers -= countDesert;
	int diceNumbers[18] = { 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 3, 4, 5, 6, 8, 9, 10, 11 };
	std::vector<int> tileDiceNumbers;
	
	for (int i = 0; i < tileToAssignNumbers; i++ ) {
		tileDiceNumbers.push_back(diceNumbers[i%18]);
	}

	// Shuffle tables

	std::random_shuffle(std::begin(tileTypes), std::end(tileTypes));
	std::random_shuffle(std::begin(tileDiceNumbers), std::end(tileDiceNumbers));

	//
	// Assign resources and diceNumbers
	//

	int i_type = 0;
	int i_dice = 0;
	for (auto lTile : inGameTiles) {
		if (lTile->getType() == Tile::TileType::BLANK) {
			lTile->setType(tileTypes[i_type]);
			if (tileTypes[i_type] != Tile::TileType::DESERT ) {
				lTile->setDiceNumber(tileDiceNumbers[i_dice]);
				i_dice++;
			}
			i_type++;
		}
	}

	//
	// Spawn roads and locations at in-game tiles
	//
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {

			if (getTile(sf::Vector2i(i, j))->getType() == Tile::TileType::NOT_USED)
				continue;

			// For each road and location
			for (int k = 0; k < 6; k++) {
				bool isNeighbor;
				Tile* lNeighborTile1 = getTile( getNeighborTile(isNeighbor,sf::Vector2i(i, j), k));
				Tile* lNeighborTile2 = getTile( getNeighborTile(isNeighbor,sf::Vector2i(i,j),(k+1) % 6) );

				// Road 
				auto lNeighborRoad = (lNeighborTile1 != nullptr ? lNeighborTile1->getRoad((k + 3) % 6) : nullptr);

				if ( lNeighborRoad != nullptr ) {
					getTile(sf::Vector2i(i, j))->addRoad(lNeighborRoad, k);
				}
				else {
					// Create road if neighbor do not have road
					std::unique_ptr<Road> lNewRoad( new Road() );
					Roads.push_back( std::move(lNewRoad) );

					getTile(sf::Vector2i(i, j))->addRoad(Roads.back().get(), k);
				}

				// Location
				auto lNeighborLocation1 = ( lNeighborTile1 != nullptr ? lNeighborTile1->getLocation((k + 2)%6) : nullptr );
				auto lNeighborLocation2 = (	lNeighborTile2 != nullptr ? lNeighborTile2->getLocation((k + 4)%6) : nullptr );

				if (lNeighborLocation1 != nullptr || lNeighborLocation2 != nullptr) {
					// Get location from neighbor
					auto lLocation = (lNeighborLocation1 != nullptr ? lNeighborLocation1 : lNeighborLocation2);
					getTile(sf::Vector2i(i, j))->addLocation(lLocation, k);
				}
				else {
					// Create location if neighbor do not have location
					std::unique_ptr<Location> lNewLocation(new Location());
					Locations.push_back(std::move(lNewLocation));

					getTile(sf::Vector2i(i, j))->addLocation(Locations.back().get(), k);
				}
			}
		}
	}

}

void Map::ComputeRender() {
	// Load deafault tile texture to compute intervals
	sf::Texture& tmpTexture = ResourceManager::getInstance().getTexture(Catan::Textures::Name::TILE_BLANK);
	float tileOverlap = 4.f;
	float lTriangleA = (float)(tmpTexture.getSize().y) * 0.5f;	// Hex border 
	float lTriangleH = (float)(tmpTexture.getSize().x / 2.f);	// Height of triangle in hex

	float lWidth = 0;
	float lHeight = 0;

	// Offsets
	sf::Vector2f offsetLocations[6] = {
		sf::Vector2f(lTriangleH,-(lTriangleA / 2.f)),
		sf::Vector2f(lTriangleH,(lTriangleA / 2.f)),
		sf::Vector2f(0,lTriangleA),
		sf::Vector2f(-lTriangleH,(lTriangleA / 2.f)),
		sf::Vector2f(-lTriangleH,-(lTriangleA / 2.f)),
		sf::Vector2f(0,-lTriangleA),
	};

	sf::Vector2f offsetRoads[6] = {
		sf::Vector2f((lTriangleH*0.5f),-(lTriangleH * 0.86f)),
		sf::Vector2f(lTriangleH,0),
		sf::Vector2f((lTriangleH*0.5f),(lTriangleH * 0.86f)),
		sf::Vector2f(-(lTriangleH*0.5f),(lTriangleH * 0.86f)),
		sf::Vector2f(-lTriangleH,0),
		sf::Vector2f(-(lTriangleH*0.5f),-(lTriangleH * 0.86f)),
	};

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			// Set tile position
			getTile(i, j)->setPosition(sf::Vector2f(lWidth, lHeight));

			// Set locations position 
			for (int k = 0; k < 6; k++) {
				Location* lLocation = getTile(i, j)->getLocation(k);

				if (lLocation == nullptr)
					continue;

				lLocation->setPosition(sf::Vector2f(lWidth, lHeight) + offsetLocations[k]);
			}

			// Set roads position 
			for (int k = 0; k < 6; k++) {
				Road* lRoad = getTile(i, j)->getRoad(k);

				if (lRoad == nullptr)
					continue;

				lRoad->setPosition(sf::Vector2f(lWidth, lHeight) + offsetRoads[k]);
			}

			// Next
			lWidth += lTriangleH * 2.f - tileOverlap;
		}

		lWidth = -(lTriangleH * (i + 1));
		lHeight -= lTriangleA * 1.5f - tileOverlap;
	}

	// Center screen on map and zoom
	sf::View lView;
	sf::Vector2f lOppositeTile = getTile(height - 1, width - 1)->getPosition();

	lView = renderWindow->getView();
	lView.setCenter(sf::Vector2f(lOppositeTile.x / 2.f, lOppositeTile.y / 2.f));
	lView.zoom(0.99f);

	renderWindow->setView(lView);
}

void Map::Show(sf::RenderWindow & _window)
{
	// Draw tiles
	for( auto& lTile : inGameTiles ){		
		lTile->draw(_window);
	}

	// Draw locations
	for (auto& lLocation : Locations) {

		sf::CircleShape lCircle(10);
		lCircle.setOrigin(10, 10);
		lCircle.setFillColor(lLocation->color == 1 ? sf::Color::Red : sf::Color::Green);
		lCircle.setPosition( lLocation->getPosition() );

		_window.draw( lCircle );
	}

	// Draw roads
	for (auto& lRoad : Roads) {

		sf::CircleShape lCircle(10);
		lCircle.setOrigin(10, 10);
		lCircle.setFillColor(sf::Color::Blue);
		lCircle.setPosition(lRoad->getPosition());

		_window.draw(lCircle);
	}

}

Map::Map(int _width, int _height, Style _style, sf::RenderWindow* _window) : width{ _width }, height{ _height }, style{ _style }, renderWindow{_window}
{

}

sf::Vector2i Map::getNeighborTile(bool & _status, sf::Vector2i _sourceTile, int _number)
{
	sf::Vector2i lReturn( _sourceTile );
	_status = true;

	switch (_number) {
		case 0: lReturn.x++; lReturn.y++; break;
		case 1: lReturn.y++; break;
		case 2: lReturn.x--; break;
		case 3: lReturn.y--; lReturn.x--; break;
		case 4: lReturn.y--; break;
		case 5: lReturn.x++; break;
		default: break;
	}

	if (!(lReturn.x >= 0 && lReturn.x < this->width &&
		lReturn.y >= 0 && lReturn.y < this->height)) {
		
		lReturn.x = -1;
		lReturn.y = -1;
		_status = false;
	}

	return lReturn;
}

Map::~Map()
{
}

Tile * Map::getTile(sf::Vector2i _vector)
{
	if (_vector.x < width && _vector.x >= 0 && _vector.y < height && _vector.y >= 0)
		return &(tiles[_vector.x][_vector.y]);
	else
		return nullptr;
}

Tile * Map::getTile(int _x, int _y)
{
	return getTile(sf::Vector2i(_x, _y));
}



