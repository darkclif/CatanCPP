#include "DrawableEntity.h"

DrawableEntity::~DrawableEntity()
{
}

sf::Vector2f DrawableEntity::getPosition()
{
	return position;
}

void DrawableEntity::setPosition(sf::Vector2f _position)
{
	position = _position;
}

sf::Vector2f DrawableEntity::getAbsolutePosition()
{
	if (parent != nullptr) {
		return position + parent->getPosition();
	}
	else {
		return position;
	}
}

float DrawableEntity::getRotation()
{
	return rotation;
}

void DrawableEntity::setRotation( float _rotation)
{
	rotation = _rotation;
}

void DrawableEntity::setParent(DrawableEntity * _parent)
{
	parent = _parent;
}
