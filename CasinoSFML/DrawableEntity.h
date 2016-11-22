#pragma once
#include <SFML/Graphics.hpp>

class DrawableEntity
{
public:
	sf::Vector2f		getPosition();
	void				setPosition(sf::Vector2f _position);

	const sf::IntRect& 	getTextureRect() const;
	void 				setTextureRect(const sf::IntRect& _rect);

	float				getRotation();
	void				setRotation(float _rotation);

	DrawableEntity*		getParent();
	void				setParent(DrawableEntity* _parent);

	sf::Vector2f		getAbsolutePosition();
	void				setTexture(sf::Texture& _texture);
	const sf::Sprite	getSprite();

	bool				isPointInEntity(sf::Vector2f _point);

	virtual void		draw(sf::RenderWindow& _window) = 0;

	DrawableEntity() : parent{ nullptr } {}

	DrawableEntity(sf::Vector2f _position, float _rotation, DrawableEntity* _parent) : parent{_parent}{
		sprite.setPosition(_position);
		sprite.setRotation(_rotation);
	}

	virtual ~DrawableEntity();

protected:
	virtual sf::Texture& getTexture() = 0;

private:
	DrawableEntity* parent;	
	sf::Sprite		sprite;
};
