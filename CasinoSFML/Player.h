#pragma once

#include <string>
#include "SFML/Graphics.hpp"

class Player
{
public:
	Player();
	~Player();

private:
	std::string name;
	sf::Color color;
};

