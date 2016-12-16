#include "Location.h"
#include "Console.h"
#include "ResourceManager.h"

#include "Road.h"

#include <cstdlib>
#include <ctime>

namespace Catan {

	Location::Location() : SelectableMapItem(SelectableMapItem::Mode::LOCATION)
	{
		type = Type::NONE;
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

	bool Location::isNeighbourLocation()
	{
		for (Road* lRoad : arrRoads) {
			for (Location* lLocation : lRoad->getLocations()) {
				if (lLocation == this)
					continue;

				if (lLocation->getType() != Location::Type::NONE)
					return true;
			}
		}

		return false;
	}

	bool Location::isNearPlayerRoad(Player * _player)
	{
		for (auto& lRoad : arrRoads) {
			if (lRoad->getOwner() == _player)
				return true;
		}

		return false;
	}

	sf::Texture & Location::getTexture()
	{
		Textures::Name lTextureName;

		switch (type) {
		case Type::CITY:	lTextureName = Textures::Name::CITY; break;
		case Type::VILLAGE: lTextureName = Textures::Name::VILLAGE; break;
		default:			lTextureName = Textures::Name::VILLAGE; break;
		}

		return ResourceMgr.getTexture(lTextureName);
	}

	void Location::draw(sf::RenderWindow& _window)
	{
		setTexture(getTexture());
		sf::Sprite tmpSprite(getSprite());

		if (hasOwner())
			tmpSprite.setColor(getOwner()->getColor());
		else
			tmpSprite.setColor(sf::Color(0, 0, 0, 0));

		if (isHighlighted()) {
			sf::Color tmpColor;

			if (hasOwner()) {
				tmpColor = getOwner()->getColor();
				tmpColor.a = 100;
			}
			else {
				tmpColor = sf::Color(255, 255, 255, 100);
			}

			tmpSprite.setColor(tmpColor);

			if (getType() == Type::VILLAGE)
				tmpSprite.setTexture(ResourceMgr.getTexture(Textures::CITY));
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

	void Location::setBonus(Bonus _bonus)
	{
		bonus = _bonus;
	}

	Location::Bonus Location::getBonus()
	{
		return bonus;
	}

	void Location::Build(Type _type, Player * _player, RoundType _round)
	{
		setType(_type);
		setOwner(_player);
		setBuildRound(_round);
	}

}