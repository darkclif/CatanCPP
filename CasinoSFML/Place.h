#pragma once

#include "Player.h"
#include <SFML/Graphics.hpp>

class Place
{
public:
	Player* getOwner() { return owner; }

	sf::Vector2f getPosition();
	void setPosition( sf::Vector2f _position );

protected:
	Player* owner;

	sf::Vector2f position;

	Place() : owner{ nullptr }, position{sf::Vector2f()} {
	}

	Place(Player* _owner) : owner{ _owner }, position{ sf::Vector2f() } {
	};

	virtual ~Place() = 0;
};

