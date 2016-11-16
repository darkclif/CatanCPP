#pragma once
#include "DrawableEntity.h"

#include <vector>
#include <iostream>

class Location;

class Road : public DrawableEntity
{
public:
	Road();
	~Road();

	// Control two locations
	bool addLocation(Location* _location);
	const std::vector<Location*>& Road::getLocations();

	sf::Texture& getTexture();
	void draw( sf::RenderWindow& _window );

	// TEST
	sf::Color color = sf::Color::White;
private:

	std::vector<Location*> arrLocations;
};
