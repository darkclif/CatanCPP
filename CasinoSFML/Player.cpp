#include "Player.h"
#include "Console.h"

namespace Catan {

	Player::Player(std::string _name, sf::Color _color, Textures::Name _avatar)
	{
		name = _name;
		color = _color;
		avatarTexture = _avatar;
		winPoints = 0;

		buildingsInRound.insert({ RoundType::BEGINNING_FORWARD, PhaseBuildings() });
		buildingsInRound.insert({ RoundType::BEGINNING_BACKWARD, PhaseBuildings() });

		items.insert({ Item::ROAD, ItemCount(15) }); // ROAD
		items.insert({ Item::CITY, ItemCount(4) }); // CITY
		items.insert({ Item::VILLAGE, ItemCount(5) }); // VILLAGE
	}

	Player::~Player()
	{
	}

	Player::PhaseBuildings Player::getPhaseState(RoundType _type)
	{
		return buildingsInRound.at(_type);
	}

	void Player::setPhaseState(RoundType _type, Item _item)
	{
		if (_item == Item::ROAD)
			buildingsInRound.at(_type).road = true;
		if (_item == Item::VILLAGE)
			buildingsInRound.at(_type).village = true;
	}

	void Player::giveResources(ResourceBag _bag)
	{
		Console::info << "Player '" << this->name << "' get resources: " << _bag.print() << std::endl;

		playerResources += _bag;
	}

	ResourceBag Player::getResources() const
	{
		return playerResources;
	}

	void Player::takeResources(ResourceBag _bag)
	{
		if (_bag >= playerResources) {
			Console::debug << "You took more resources from player than he already has!" << std::endl;
		}

		playerResources -= _bag;
	}

	int Player::getItem(Item _item) const
	{
		return items.at(_item).count;
	}

	void Player::takeItem(Item _item, int _count)
	{
		if (_count > getItem(_item)) {
			Console::debug << "Trying to get more items (roads/cities/villages) than player already has!" << std::endl;
			items.at(_item).count = 0;
		}

		items.at(_item).count -= _count;

		recalculateWinPoints();
	}

	void Player::giveItem(Item _item, int _count)
	{
		if (_count <= 0)
			return;

		items.at(_item).count += _count;

		if (items.at(_item).count > items.at(_item).MAX)
			items.at(_item).count = items.at(_item).MAX;

		recalculateWinPoints();
	}

	void Player::recalculateWinPoints()
	{
		int lWP = 0;

		lWP += 1 * (items.at(Item::VILLAGE).MAX - items.at(Item::VILLAGE).count);
		lWP += 2 * (items.at(Item::CITY).MAX - items.at(Item::CITY).count);

		winPoints = lWP;
	}

	int Player::getWinPoints() const
	{
		return winPoints;
	}

	std::string Player::getName() const
	{
		return name;
	}

	sf::Color Player::getColor() const
	{
		return color;
	}

	Textures::Name Player::getAvatarTexture() const
	{
		return avatarTexture;
	}

}