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

	void setParent( DrawableEntity* _parent );

	virtual void draw( sf::RenderWindow& _window) = 0;

	DrawableEntity() : position{ sf::Vector2f() }, rotation{ 0.f }, parent{ nullptr } {
	}

	DrawableEntity(sf::Vector2f _position, float _rotation, DrawableEntity* _parent) :
		position{ _position }, rotation{ _rotation }, parent{_parent}{
	}

	virtual ~DrawableEntity();
protected:
	sf::Vector2f position;
	float rotation;

	DrawableEntity* parent;
	
	virtual sf::Texture& getTexture() = 0;
};
