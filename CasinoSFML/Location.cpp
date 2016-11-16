#include "Location.h"
#include "Console.h"
#include "ResourceManager.h"

#include <cstdlib>
#include <ctime>

Location::Location()
{
	type = Type::VILLAGE;
	bonus = Bonus::NONE;
}

Location::~Location()
{
}

bool Location::addRoad(Road * _road)
{
	for (std::vector<Road*>::iterator it = arrRoads.begin(); it != arrRoads.end(); it++) {
		if (_road == *it) return false;
	}

	// Only three roads beside the location
	if (arrRoads.size() == 3) {
		Console::debug << "Too many unique roads at single location!" << std::endl;
		return false;
	}

	arrRoads.push_back(_road);
	return true;
}

const std::vector<Road*>& Location::getRoads()
{
	return arrRoads;
}

sf::Texture & Location::getTexture()
{
	Catan::Textures::Name lTextureName;

	switch (type) {
		case CITY: lTextureName = Catan::Textures::Name::CITY; break;
		case VILLAGE: lTextureName = Catan::Textures::Name::VILLAGE; break;
		default: lTextureName = Catan::Textures::Name::TEXTURE_EMPTY; break;
	}

	return ResourceManager::getInstance().getTexture(lTextureName);
}

void Location::draw(sf::RenderWindow& _window)
{
	sf::Sprite lSprite(getTexture());

	sf::Rect<int> lOrigin(lSprite.getTextureRect());
	lOrigin.height /= 2;
	lOrigin.width /= 2;

	lSprite.setOrigin((float)lOrigin.width, (float)lOrigin.height);
	lSprite.setPosition(getPosition());

	_window.draw(lSprite);
}

void Location::setType(Type _type)
{
	type = _type;
}

Location::Type Location::getType()
{
	return type;
}
