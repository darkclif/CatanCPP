#pragma once
#include <SFML/Graphics.hpp>

class DrawableEntity
{
public:
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f _position);

	sf::Vector2f getAbsolutePosition();

	float getRotation();
	void setRotation( float _rotation);

	DrawableEntity* getParent();
	void setParent( DrawableEntity* _parent );

	virtual void draw(sf::RenderWindow& _window) = 0;
	void setTexture( sf::Texture& _texture );
	const sf::Sprite getSprite();

	bool isPointInEntity(sf::Vector2f _point);

	DrawableEntity() : parent{ nullptr } {}

	DrawableEntity(sf::Vector2f _position, float _rotation, DrawableEntity* _parent) : parent{_parent}{
		sprite.setPosition(_position);
		sprite.setRotation(_rotation);
	}

	virtual ~DrawableEntity();
private:
	sf::Sprite sprite;
	DrawableEntity* parent;
	
	virtual sf::Texture& getTexture() = 0;
};
