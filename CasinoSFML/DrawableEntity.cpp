#include "DrawableEntity.h"
#include "Functions.h"

DrawableEntity::~DrawableEntity()
{
}

sf::Vector2f DrawableEntity::getPosition()
{
	return sprite.getPosition();
}

void DrawableEntity::setPosition(sf::Vector2f _position)
{
	sprite.setPosition( _position);
}

const sf::IntRect & DrawableEntity::getTextureRect() const
{
	return sprite.getTextureRect();
}

void DrawableEntity::setTextureRect(const sf::IntRect & _rect)
{
	sprite.setTextureRect(_rect);
}

sf::Vector2f DrawableEntity::getAbsolutePosition()
{
	if (parent != nullptr) {
		return sprite.getPosition() + parent->getPosition();
	}
	else {
		return sprite.getPosition();
	}
}

float DrawableEntity::getRotation()
{
	return sprite.getRotation();
}

void DrawableEntity::setRotation( float _rotation)
{
	sprite.setRotation( _rotation );
}

void DrawableEntity::setScale(float _x, float _y)
{
	sprite.setScale(_x,_y);
}

sf::Vector2f DrawableEntity::getScale()
{
	return sprite.getScale();
}

DrawableEntity * DrawableEntity::getParent()
{
	return parent;
}

void DrawableEntity::setParent(DrawableEntity * _parent)
{
	parent = _parent;
}

void DrawableEntity::setTexture(sf::Texture & _texture)
{
	sprite.setTexture( _texture );

	sf::Rect<int> lOrigin(sprite.getTextureRect());
	lOrigin.height /= 2;
	lOrigin.width /= 2;

	sprite.setOrigin((float)lOrigin.width, (float)lOrigin.height);
}

void DrawableEntity::setOriginAtCenter()
{
	Catan::setOriginAtCenter(sprite);
}

const sf::Sprite DrawableEntity::getSprite()
{
	return sprite;
}

sf::FloatRect DrawableEntity::getSpriteGlobalBounds()
{
	return sprite.getGlobalBounds();
}

bool DrawableEntity::isPointInEntity(sf::Vector2f _point)
{
	sf::FloatRect tmpRect = getSprite().getGlobalBounds();

	if (tmpRect.contains(_point))
		return true;
	else
		return false;
}
