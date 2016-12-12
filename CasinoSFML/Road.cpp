#include "Road.h"
#include "Console.h"
#include "ResourceManager.h"
#include "Location.h"

Road::Road(): SelectableMapItem(SelectableMapItem::Mode::ROAD)
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

bool Road::isNeighbourWithLocation(Player * _player, RoundType _round)
{
	for (auto& lLocation : arrLocations ) {
		if (((char)lLocation->getBuildRound() & (char)_round) && (lLocation->getOwner() == _player))
			return true;
	}
	return false;
}

bool Road::isBesidePlayerItem(Player * _player)
{
	for (auto& lLocation : arrLocations) {
		if (lLocation->getOwner() == _player)
			return true;

		for (auto& lRoad : lLocation->getRoads()) {
			if (lRoad == this)
				continue;

			if (lRoad->getOwner() == _player)
				return true;
		}
	}
	return false;
}
