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

void Road::setRotation(float _rotation)
{
	rotation = _rotation;
}

float Road::getRoatation()
{
	return rotation;
}

sf::Texture & Road::getTexture()
{
	auto lTextureName = Catan::Textures::Name::ROAD;
	return ResourceManager::getInstance().getTexture(lTextureName);
}

void Road::draw(sf::RenderWindow& _window)
{
	sf::Sprite lSprite(getTexture());

	sf::Rect<int> lOrigin(lSprite.getTextureRect());
	lOrigin.height /= 2;
	lOrigin.width /= 2;

	lSprite.setOrigin((float)lOrigin.width, (float)lOrigin.height);
	lSprite.setPosition(getPosition());
	lSprite.setRotation(getRoatation());
	// lSprite.setColor( getOwner->getColor() );

	_window.draw(lSprite);
}
