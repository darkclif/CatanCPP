#pragma once
#include <SFML/Graphics.hpp>

namespace Catan {

	class DrawableEntity
	{
	public:
		sf::Vector2f		getPosition();
		void				setPosition(sf::Vector2f _position);

		const sf::IntRect& 	getTextureRect() const;
		void 				setTextureRect(const sf::IntRect& _rect);

		float				getRotation();
		void				setRotation(float _rotation);

		void				setScale(float _x, float _y);
		sf::Vector2f		getScale();

		DrawableEntity*		getParent();
		void				setParent(DrawableEntity* _parent);

		sf::Vector2f		getAbsolutePosition();
		void				setTexture(sf::Texture& _texture);

		void				setOriginAtCenter();

		const sf::Sprite	getSprite();
		sf::FloatRect		getSpriteGlobalBounds();

		virtual bool		isPointInEntity(sf::Vector2f _point);

		DrawableEntity() : parent{ nullptr } {}

		DrawableEntity(sf::Vector2f _position, float _rotation, DrawableEntity* _parent) : parent{ _parent } {
			sprite.setPosition(_position);
			sprite.setRotation(_rotation);
		}

		virtual void		draw(sf::RenderWindow& _window) = 0;

		virtual ~DrawableEntity();

	protected:
		virtual sf::Texture& getTexture() = 0;

	private:
		DrawableEntity* parent;
		sf::Sprite		sprite;
	};

}