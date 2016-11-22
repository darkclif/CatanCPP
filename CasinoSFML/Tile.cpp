#include "Tile.h"

#include <iostream>

#include "Console.h"
#include "ResourceBag.h"
//
// Dice number
//
const Catan::Textures::Name DiceNumber::arrDiceToTexture[11] = {
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

void DiceNumber::draw(sf::RenderWindow & _window)
{
	setTexture(getTexture());

	sf::Sprite tmpSprite( getSprite() );

	if (getParent() != nullptr)
		tmpSprite.setPosition( getAbsolutePosition());

	_window.draw(tmpSprite);
}

void DiceNumber::setNumber(int _number)
{
	if (_number > 1 && _number < 13 && _number != 7)
		number = _number;
	else
		Console::debug << "Wrong dice number given to setNumber" << std::endl;
}

sf::Texture & DiceNumber::getTexture()
{
	if (number > 1 && number < 13) {
		Catan::Textures::Name lTextureName = arrDiceToTexture[number - 2];
		return ResourceManager::getInstance().getTexture(lTextureName);
	}
	else {
		return ResourceManager::getInstance().getTexture(Catan::Textures::TEXTURE_EMPTY);
	}
}

//
// Thief
//
void Thief::draw(sf::RenderWindow & _window)
{
	setTexture(getTexture());

	sf::Sprite tmpSprite(getSprite());

	if (getParent() != nullptr)
		tmpSprite.setPosition(getAbsolutePosition());

	_window.draw(tmpSprite);
}

sf::Texture & Thief::getTexture()
{
	Catan::Textures::Name lTextureName = Catan::Textures::THIEF;
	return ResourceManager::getInstance().getTexture(lTextureName);
}

//
// Tile
//
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

const std::map<Tile::TileType, Resource> Tile::mapTypeToResource = {
	{TileType::WOOD,Resource::WOOD},
	{TileType::SHEEP,Resource::SHEEP},
	{TileType::CLAY,Resource::CLAY},
	{TileType::IRON,Resource::IRON},
	{TileType::WHEAT,Resource::WHEAT}
};

Tile::Tile() : type{ NOT_USED }, diceNumber{ 0 }, initJump{ 0 } {
	std::unique_ptr<Thief> tmpThief(new Thief(sf::Vector2f(100.f, -80.f), this));
	thiefEntity = std::move(tmpThief);
	
	std::unique_ptr<DiceNumber> tmpNumber(new DiceNumber(sf::Vector2f(0.f, 0.f), this));
	numberEntity = std::move(tmpNumber);

	arrLocations.resize(6);
	arrRoads.resize(6);

	for (int i = 0; i < 6; i++) {
		arrLocations[i] = nullptr;
		arrRoads[i] = nullptr;
	}
}

Tile::Tile(TileType _type, unsigned int _number) : type{ _type }, diceNumber{ _number }, initJump{ 0 } {
	Tile();
	
	numberEntity->setNumber(_number);
	setType(_type);
};

Tile::~Tile()
{
};

bool Tile::isThief()
{
	return thief;
}

void Tile::setThief(bool _thief)
{
	thief = _thief;
}

void Tile::giveResourceToPlayers()
{
	for (auto& lLocation : arrLocations) {
		if ( lLocation->hasOwner()) {
			Player* lPlayer = lLocation->getOwner();
			int lCount = (lLocation->getType() == Location::CITY ? 2 : 1);

			ResourceBag lResourceBag(lCount, getResourceType());
			lPlayer->giveResources(lResourceBag);
		}
	}
}

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
	if (_number > 1 && _number < 13 && _number != 7) {
		diceNumber = _number;
		numberEntity->setNumber(_number);
	}
	else {
		Console::debug << "Wrong dice number given to setDiceNumber" << std::endl;
	}
}

sf::Texture& Tile::getTexture()
{
	Catan::Textures::Name lTextureName = arrTileToTexture[(int)type];
	return ResourceManager::getInstance().getTexture( lTextureName );
}



void Tile::draw(sf::RenderWindow &_window)
{
	setTexture(getTexture());

	sf::Sprite tmpSprite(getSprite());

	if (getParent() != nullptr)
		tmpSprite.setPosition(getAbsolutePosition());

	_window.draw(tmpSprite);

	if (isThief() && thiefEntity != nullptr ) thiefEntity->draw(_window);
	if (diceNumber != 7 && numberEntity != nullptr ) numberEntity->draw(_window);
}

bool Tile::addRoad(Road * _road, int _number)
{
	if (arrRoads[_number] != nullptr) {
		if (arrRoads[_number] == _road) {
			// Given pointer is already here
			return false;
		}
		else {
			// Two diffrent roads on one edge
			Console::debug << "You are trying to assign two diffrent roads on one edge!" << std::endl;
			throw std::logic_error("");
		}
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
			// Two diffrent locations on one place
			Console::debug << "You are trying to assign two diffrent locations on one place!" << std::endl;
			throw std::logic_error("");
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

bool Tile::bindRoadsLocations()
{
	for (int i = 0; i < 6; i++) {
		Location* lLocation = getLocation(i);
		
		if (lLocation == nullptr) {
			Console::debug << "Failed to link sorroundings at tile. Location is null." << std::endl;
			return false;
		}

		lLocation->addRoad(getRoad(i));
		lLocation->addRoad(getRoad((i + 1) % 6));

		Road* lRoad1 = getRoad(i);
		Road* lRoad2 = getRoad((i + 1) % 6);

		if (lRoad1 == nullptr || lRoad2 == nullptr) {
			Console::debug << "Failed to link sorroundings at tile. Road is null." << std::endl;
			return false;
		}

		lRoad1->addLocation(lLocation);
		lRoad2->addLocation(lLocation);
	}

	return true;
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

Resource Tile::getResourceType()
{
	return mapTypeToResource.find(type)->second;
}
