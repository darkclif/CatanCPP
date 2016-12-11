#pragma once
#include "DrawableEntity.h"
#include "SelectableMapItem.h"

#include <vector>
#include <iostream>
#include "PlayerEntity.h"

class Location;

class Road : public DrawableEntity, public SelectableMapItem, public PlayerEntity
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
