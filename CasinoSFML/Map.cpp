#include "Map.h"

#include "PlayerGUI.h"

#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <stdlib.h>

Map::Map(sf::RenderWindow* _window) : width(Map::MAP_EDGE), height(Map::MAP_EDGE), renderWindow{ _window }, selectionMode{NONE}
{
	// Make a square map
	this->tiles.resize(height);
	for (int i = 0; i < height; i++) {
		tiles[i].resize(width);
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::unique_ptr<Tile> tmpPtr(new Tile());
			tiles[i][j] = std::move(tmpPtr);
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
	int x = 2;
	int y = 2;
	int lRadius = 3;
	
	// Add center tile to queue and start spreading map 
	std::queue<sf::Vector2i> qTileToInit;

	getTile(x, y)->setInitJump(1);
	getTile(x, y)->setType(Tile::TileType::DESERT);
	getTile(x, y)->setThief(true);

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

	// Prepare resources and numbers to assign
	std::vector<Tile::TileType> tileTypes;
	std::vector<int> tileDiceNumbers;

	Tile::TileType lTiles[] = {
		Tile::TileType::SHEEP, Tile::TileType::SHEEP, Tile::TileType::SHEEP, Tile::TileType::SHEEP,
		Tile::TileType::WOOD, Tile::TileType::WOOD, Tile::TileType::WOOD, Tile::TileType::WOOD,
		Tile::TileType::WHEAT, Tile::TileType::WHEAT, Tile::TileType::WHEAT, Tile::TileType::WHEAT,
		Tile::TileType::IRON, Tile::TileType::IRON, Tile::TileType::IRON,
		Tile::TileType::CLAY, Tile::TileType::CLAY, Tile::TileType::CLAY
	};
	int lDiceNumbers[18] = { 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 3, 4, 5, 6, 8, 9, 10, 11 };

	tileTypes.insert(tileTypes.begin(), lTiles, lTiles + 18);
	tileDiceNumbers.insert(tileDiceNumbers.begin(), lDiceNumbers, lDiceNumbers + 18);

	// Shuffle tables
	std::random_shuffle(std::begin(tileTypes), std::end(tileTypes));
	std::random_shuffle(std::begin(tileDiceNumbers), std::end(tileDiceNumbers));

	// Assign resources and diceNumbers
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
			Tile* currTile = getTile(i,j);

			if (currTile->getType() == Tile::TileType::NOT_USED)
				continue;

			// Spawn roads and locations
			SpawnAtTile( currTile, i, j);
			getTile(i,j)->bindRoadsLocations();
		}
	}

}

void Map::SpawnAtTile( Tile* currTile, int i, int j) {
	// Spawn roads and locations for single tile
	for (int k = 0; k < 6; k++) {
		bool isNeighbor;
		Tile* lNeighborTile1 = getTile(getNeighborTile(isNeighbor, sf::Vector2i(i, j), k));
		Tile* lNeighborTile2 = getTile(getNeighborTile(isNeighbor, sf::Vector2i(i, j), (k + 1) % 6));

		// Road 
		auto lNeighborRoad = (lNeighborTile1 != nullptr ? lNeighborTile1->getRoad((k + 3) % 6) : nullptr);

		if (lNeighborRoad != nullptr) {
			currTile->addRoad(lNeighborRoad, k);
		}
		else {
			// Create road if neighbor do not have road
			std::unique_ptr<Road> lNewRoad(new Road());
			Roads.push_back(std::move(lNewRoad));

			currTile->addRoad(Roads.back().get(), k);
		}

		// Location
		auto lNeighborLocation1 = (lNeighborTile1 != nullptr ? lNeighborTile1->getLocation((k + 2) % 6) : nullptr);
		auto lNeighborLocation2 = (lNeighborTile2 != nullptr ? lNeighborTile2->getLocation((k + 4) % 6) : nullptr);

		if (lNeighborLocation1 != nullptr || lNeighborLocation2 != nullptr) {
			// Get location from neighbor
			auto lLocation = (lNeighborLocation1 != nullptr ? lNeighborLocation1 : lNeighborLocation2);
			currTile->addLocation(lLocation, k);
		}
		else {
			// Create location if neighbor do not have location
			std::unique_ptr<Location> lNewLocation(new Location());
			Locations.push_back(std::move(lNewLocation));

			currTile->addLocation(Locations.back().get(), k);
		}

	}/* end of spawn */
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

	float rotationRoads[6] = {30.f, 90.f, -30.f, 30.f, 90.f, -30.f};

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

				lRoad->setRotation(rotationRoads[k]);
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

void Map::Draw(sf::RenderWindow & _window)
{
	for( auto& lTile : inGameTiles ){		
		lTile->draw(_window);
	}

	for (auto& lRoad : Roads) {
		lRoad->draw(_window);
	}

	for (auto& lLocation : Locations) {
		lLocation->draw(_window);
	}
}

void Map::HandleEvent(sf::Event _event)
{
	if (highlightedItem != nullptr)
		highlightedItem->setHighlight(false);

	if ( _event.type == _event.MouseMoved ) {
		if (selectionMode != SelectionMode::NONE) {
			checkItemsForHighlight(_event);
		}
	}

	if (_event.type == _event.MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left) {
		if (selectionMode != SelectionMode::NONE) {
			checkItemsForClick(_event);
		}
	}
}

void Map::Update(sf::Time _dt)
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

void Map::getSelection(SelectionMode _mode, PlayerGUI* _playerGUI)
{
	playerGUI = _playerGUI;
	selectionMode = _mode;
}

void Map::closeSelection()
{
	selectionMode = SelectionMode::NONE;
}

void Map::acceptDiceThrow(int _dicesum)
{
	if (_dicesum == 7)
		return;

	for (auto& lTile : inGameTiles) {
		if(lTile->getDiceNumber() == _dicesum ){
			lTile->giveResourceToPlayers();
		}
	}
}

void Map::sendCallbackFunction(SelectableMapItem * _item)
{
	Console::debug << "Send callback to PlayerGUI!" << std::endl;
	selectionMode = SelectionMode::NONE;
	playerGUI->acceptSelection(_item);
}

void Map::checkItemsForClick(sf::Event _event )
{
	int x = _event.mouseButton.x;
	int y = _event.mouseButton.y;
	sf::Vector2f point = renderWindow->mapPixelToCoords(sf::Vector2i(x, y));

	switch (selectionMode) {
		case SelectionMode::SELECT_LOCATION:
			for (auto& lLocation : Locations) {
				if (lLocation->isPointInEntity(point)) {
					this->sendCallbackFunction(lLocation.get());
					break;
				}
			}
			break;
		case SelectionMode::SELECT_ROAD:
			for (auto& lRoad : Roads) {
				if (lRoad->isPointInEntity(point)) {
					this->sendCallbackFunction(lRoad.get());
					break;
				}
			}
			break;
		case SelectionMode::SELECT_TILE:
			for (auto lTile : inGameTiles) {
				if (lTile->isPointInEntity(point)) {
					//this->sendCallbackFunction(lTile);
					break;
				}
			}
			break;
		default:
			break;
	}	
	
}

void Map::checkItemsForHighlight(sf::Event _event)
{
	int x = _event.mouseMove.x;
	int y = _event.mouseMove.y;
	sf::Vector2f point = renderWindow->mapPixelToCoords(sf::Vector2i(x, y));

	switch (selectionMode) {
	case SelectionMode::SELECT_LOCATION:
		for (auto& lLocation : Locations) {
			if (lLocation->isPointInEntity(point)) {
				lLocation->setHighlight(true);
				highlightedItem = lLocation.get();
				break;
			}
		}
		break;
	case SelectionMode::SELECT_ROAD:
		for (auto& lRoad : Roads) {
			if (lRoad->isPointInEntity(point)) {
				lRoad->setHighlight(true);
				highlightedItem = lRoad.get();
				break;
			}
		}
		break;
	case SelectionMode::SELECT_TILE:
		for (auto lTile : inGameTiles) {
			if (lTile->isPointInEntity(point)) {
				//this->sendCallbackFunction(lTile);
				break;
			}
		}
		break;
	default:
		break;
	}

}

Map::~Map()
{
}

Tile * Map::getTile(sf::Vector2i _vector)
{
	if (_vector.x < width && _vector.x >= 0 && _vector.y < height && _vector.y >= 0)
		return tiles[_vector.x][_vector.y].get();
	else
		return nullptr;
}

Tile * Map::getTile(int _x, int _y)
{
	return getTile(sf::Vector2i(_x, _y));
}



