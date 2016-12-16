#include "Player.h"
#include "Console.h"

namespace Catan {

	Player::Player(std::string _name, sf::Color _color, Catan::Textures::Name _avatar)
	{
		name = _name;
		color = _color;
		avatarTexture = _avatar;
		winPoints = 0;

		items.push_back(ItemCount(15)); // ROAD
		items.push_back(ItemCount(4)); // CITY
		items.push_back(ItemCount(5)); // VILLAGE
	}

	Player::~Player()
	{
	}

	Player::PhaseBuildings Player::getPhaseState(Phase _phase)
	{
		return phaseBuilings[(int)(_phase)];
	}

	void Player::setPhaseState(Phase _phase, Item _item)
	{
		if (_item == Item::ROAD)
			phaseBuilings[(int)(_phase)].road = true;
		if (_item == Item::VILLAGE)
			phaseBuilings[(int)(_phase)].village = true;
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
		return items[(int)(_item)].count;
	}

	void Player::takeItem(Item _item, int _count)
	{
		if (_count > getItem(_item)) {
			Console::debug << "Trying to get more items (roads/cities/villages) than player already has!" << std::endl;
			items[(int)(_item)].count = 0;
		}

		items[(int)(_item)].count -= _count;

		recalculateWinPoints();
	}

	void Player::giveItem(Item _item, int _count)
	{
		if (_count <= 0)
			return;

		items[(int)(_item)].count += _count;

		if (items[(int)(_item)].count > items[(int)(_item)].MAX)
			items[(int)(_item)].count = items[(int)(_item)].MAX;

		recalculateWinPoints();
	}

	void Player::recalculateWinPoints()
	{
		int lWP = 0;

		lWP += 1 * (items[(int)Item::VILLAGE].MAX - items[(int)Item::VILLAGE].count);
		lWP += 2 * (items[(int)Item::CITY].MAX - items[(int)Item::CITY].count);

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

	Catan::Textures::Name Player::getAvatarTexture() const
	{
		return avatarTexture;
	}

}