#include "Player.h"
#include "Console.h"

Player::Player(std::string _name, sf::Color _color, Catan::Textures::Name _avatar)
{
	name = _name;
	color = _color;
	avatarTexture = _avatar;

	giveItem(Item::CITY, 4);
	giveItem(Item::VILLAGE, 5);
	giveItem(Item::ROAD, 15);
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
	if ( _bag >= playerResources ) {
		Console::debug << "You took more resources from player than he already has!" << std::endl;
	}

	playerResources -= _bag;
}

int Player::getItem(Item _item) const
{
	return items[(int)(_item)];
}

void Player::takeItem(Item _item, int _count)
{
	if ( _count > getItem(_item)) {
		Console::debug << "Trying to get more items (roads/cities/villages) than player already has!" << std::endl;
		items[(int)(_item)] = 0;
	}

	items[(int)(_item)] -= _count;
}

void Player::giveItem(Item _item, int _count)
{
	if (_count <= 0)
		return;

	items[(int)(_item)] += _count;
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
