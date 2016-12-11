#include "Location.h"
#include "Console.h"
#include "ResourceManager.h"

#include <cstdlib>
#include <ctime>

Location::Location(): SelectableMapItem( SelectableMapItem::Type::LOCATION )
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
	setTexture(getTexture());
	sf::Sprite tmpSprite(getSprite());
	
	if (hasOwner()) {
		tmpSprite.setColor(getOwner()->getColor());
	}
	else {
		if (!isHighlighted())
			tmpSprite.setColor(sf::Color(0, 0, 0, 0));
		else
			tmpSprite.setColor(sf::Color(255, 255, 255, 100));
	}

	if (getParent() != nullptr)
		tmpSprite.setPosition(getAbsolutePosition());

	_window.draw(tmpSprite);
}

void Location::setType(Type _type)
{
	type = _type;
}

Location::Type Location::getType()
{
	return type;
}
