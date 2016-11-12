#include "Place.h"

sf::Vector2f Place::getPosition()
{
	return position;
}

void Place::setPosition(sf::Vector2f _position)
{
	position = _position;
}

Place::~Place()
{
}
