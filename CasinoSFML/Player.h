#pragma once

#include <string>

#include "SFML/Graphics.hpp"

#include "resources/Textures.h"
#include "ResourceBag.h"

class Player
{
public:

	Player( std::string _name, sf::Color _color, Catan::Textures::Name _avatar);
	~Player();

	void giveResources( ResourceBag _bag);

private:
	// Player info
	Catan::Textures::Name	avatarTexture;
	std::string				name;
	sf::Color				color;

	ResourceBag				playerResources;
};

