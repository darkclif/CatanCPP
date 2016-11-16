#include "Road.h"
#include "Console.h"
#include "ResourceManager.h"

Road::Road()
{
}

Road::~Road()
{
}

bool Road::addLocation(Location * _location)
{
	for (auto it = arrLocations.begin(); it != arrLocations.end(); it++) {
		if (_location == *it) return false;
	}

	// Only two locations beside the road 
	if (arrLocations.size() == 2) {
		Console::debug << "Too many unique locations at signle road!" << std::endl;
		return false;
	}

	arrLocations.push_back(_location);
	return true;
}

const std::vector<Location*>& Road::getLocations()
{
	return arrLocations;
}

sf::Texture & Road::getTexture()
{
	auto lTextureName = Catan::Textures::Name::ROAD;
	return ResourceManager::getInstance().getTexture(lTextureName);
}

void Road::draw(sf::RenderWindow& _window)
{
	setTexture(getTexture());

	sf::Sprite tmpSprite(getSprite());

	if (getParent() != nullptr)
		tmpSprite.setPosition(getAbsolutePosition());

	// TEST
	tmpSprite.setColor(color);

	_window.draw(tmpSprite);
}
