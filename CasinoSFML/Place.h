#pragma once

#include "Player.h"
#include <SFML/Graphics.hpp>

class Place
{
public:
	sf::Vector2f getPosition();
	void setPosition( sf::Vector2f _position );

protected:
	sf::Vector2f position;

	Place() : position{sf::Vector2f()} {
	}

	Place(Player* _owner) : position{ sf::Vector2f() } {
	};

	virtual ~Place();
};

