#include "Player.h"

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
	playerResources += _bag;
}
