#include "Tile.h"

#include <iostream>
#include "Console.h"

const Catan::Textures::Name Tile::arrTileToTexture[ TileType::__ENUM_SIZE ] = {
	Catan::Textures::Name::TILE_WOOD,
	Catan::Textures::Name::TILE_SHEEP,
	Catan::Textures::Name::TILE_CLAY,
	Catan::Textures::Name::TILE_IRON,
	Catan::Textures::Name::TILE_WHEAT,
	Catan::Textures::Name::TILE_DESERT,
	Catan::Textures::Name::TILE_BLANK,	
	Catan::Textures::Name::TILE_NOT_USED,
};

const Catan::Textures::Name Tile::arrDiceToTexture[11] = {
	Catan::Textures::Name::TILE_DICE_NUM_2,	
	Catan::Textures::Name::TILE_DICE_NUM_3,
	Catan::Textures::Name::TILE_DICE_NUM_4,
	Catan::Textures::Name::TILE_DICE_NUM_5,
	Catan::Textures::Name::TILE_DICE_NUM_6,
	Catan::Textures::Name::TEXTURE_EMPTY,
	Catan::Textures::Name::TILE_DICE_NUM_8,
	Catan::Textures::Name::TILE_DICE_NUM_9,
	Catan::Textures::Name::TILE_DICE_NUM_10,
	Catan::Textures::Name::TILE_DICE_NUM_11,
	Catan::Textures::Name::TILE_DICE_NUM_12,
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
		Console::debug << "Wrong dice number given to setDiceNumber" << std::endl;
}

sf::Texture& Tile::getTexture()
{
	Catan::Textures::Name lTextureName = arrTileToTexture[(int)type];
	return ResourceManager::getInstance().getTexture( lTextureName );
}

sf::Texture& Tile::getDiceNumberTexture() {
	if (diceNumber > 1 && diceNumber < 13) {
		Catan::Textures::Name lTextureName = arrDiceToTexture[diceNumber - 2];
		return ResourceManager::getInstance().getTexture(lTextureName);
	}
	else {
		return ResourceManager::getInstance().getTexture(Catan::Textures::TEXTURE_EMPTY);
	}
}

void Tile::draw(sf::RenderWindow &_window)
{
	// Tile
	sf::Sprite lTileSprite(getTexture());

	sf::Rect<int> lOrigin(lTileSprite.getTextureRect());
	lOrigin.height /= 2;
	lOrigin.width /= 2;

	lTileSprite.setOrigin((float)lOrigin.width, (float)lOrigin.height);
	lTileSprite.setPosition(getPosition());

	_window.draw(lTileSprite);

	// Draw number
	sf::Sprite lTextSprite(getDiceNumberTexture());

	lOrigin = lTextSprite.getTextureRect();
	lOrigin.height /= 2;
	lOrigin.width /= 2;

	lTextSprite.setOrigin((float)lOrigin.width, (float)lOrigin.height);
	lTextSprite.setPosition(getPosition());

	_window.draw(lTextSprite);
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
