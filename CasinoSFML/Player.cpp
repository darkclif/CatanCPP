#include "Player.h"
#include "Console.h"

Player::Player(std::string _name, sf::Color _color, Catan::Textures::Name _avatar)
{
	name = _name;
	color = _color;
	avatarTexture = _avatar;


}


Player::~Player()
{
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
