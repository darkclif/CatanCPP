#pragma once
#include "Place.h"

#include <vector>
#include <iostream>

class Location;

class Road : public Place
{
public:
	Road();
	~Road();

	// Control two locations
	bool addLocation(Location* _location);
	const std::vector<Location*>& Road::getLocations();

	void setRotation( float _rotation );
	float getRoatation();

	sf::Texture& getTexture();
	void draw( sf::RenderWindow& _window );

private:
	float rotation = 0;

	std::vector<Location*> arrLocations;
};
