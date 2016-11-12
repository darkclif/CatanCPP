#include "Tile.h"

#include <iostream>

const Catan::Textures::Name Tile::arrTileToTexture[ TileType::__ENUM_SIZE ] = {
	Catan::Textures::Name::TILE_WOOD,	// WOOD
	Catan::Textures::Name::TILE_SHEEP,	// SHEEP		
	Catan::Textures::Name::TILE_CLAY,	// CLAY		
	Catan::Textures::Name::TILE_IRON,	// IRON		
	Catan::Textures::Name::TILE_WHEAT,	// WHEAT		
	Catan::Textures::Name::TILE_DESERT,	// DESERT		
	Catan::Textures::Name::TILE_BLANK,	// BLANK		
	Catan::Textures::Name::TILE_NOT_USED,// NOT_USED	
};

Tile::Tile(TileType _type, unsigned int _number) :
	type{ _type },
	diceNumber{ _number },
	initJump{ 0 } {

	for (int i = 0; i < 6; i++) {
		arrLocations[i] = nullptr;
		arrRoads[i] = nullptr;
	}
};

Tile::Tile() : type{ NOT_USED }, diceNumber{ 0 }, initJump{ 0 } {

	for (int i = 0; i < 6; i++) {
		arrLocations[i] = nullptr;
		arrRoads[i] = nullptr;
	}
}

Tile::~Tile()
{
};

Tile::TileType Tile::getType() {
	return type;
}

void Tile::setType(TileType _type)
{
	type = _type;
}

int Tile::getDiceNumber()
{
	return diceNumber;
}

void Tile::setDiceNumber(int _number)
{
	if (_number > 1 && _number < 13 && _number != 7)
		diceNumber = _number;
	else
		std::cout << "Wrong dice number given to setDiceNumber" << std::endl;
}

sf::Texture& Tile::getTexture()
{
	Catan::Textures::Name lTextureName = arrTileToTexture[(int)(this->type)];
	return ResourceManager::getInstance().getTexture( lTextureName );
}

bool Tile::addRoad(Road * _road, int _number)
{
	if (arrRoads[_number] != nullptr) {
		return false;
	}

	arrRoads[_number] = _road;
	return true;
}

bool Tile::addLocation(Location * _location, int _number)
{
	if (arrLocations[_number] != nullptr) {
		if (arrLocations[_number] == _location) {
			// Given pointer is already here
			return false;
		}
		else {
			// Two diffrent road on one edge ?
			std::string lError = "You are trying to assign two diffrent road on one edge \n pointer:";
			lError += std::to_string((int)arrLocations[_number]) + "->" + std::to_string((int)_location);
			std::cout << lError << std::endl;
			throw std::logic_error(lError);
		}
	}

	arrLocations[_number] = _location;
	return true;
}

Location* Tile::getLocation( int _number )
{
	if (_number >= 0 && _number < 6) {
		return this->arrLocations[_number];
	}else {
		std::string lError = "Index out of range (" + std::to_string(_number) + ") in Tile::getLocation";
		std::cout << lError << std::endl;
		throw std::logic_error(lError);
	}
}

Road* Tile::getRoad(int _number)
{
	if (_number >= 0 && _number < 6){
		return this->arrRoads[_number];
	} else {
		std::string lError = "Index out of range (" + std::to_string(_number) + ") in Tile::getRoad";
		std::cout << lError << std::endl;
		throw std::logic_error(lError);
	}
}

int Tile::getInitJump()
{
	return initJump;
}

void Tile::setInitJump(int _jump)
{
	if (_jump < 0) {
		std::string lError = "Tile::setInitJump: JumpNumber less than 0";
		std::cout << lError << std::endl;
		throw std::logic_error(lError);
	}

	this->initJump = _jump;
}
