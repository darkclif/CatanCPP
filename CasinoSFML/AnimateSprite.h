#pragma once
#include <SFML/Graphics.hpp>

#include "AnimateEntity.h"
#include "DrawableEntity.h"
#include "ResourceManager.h"
#include "resources/Textures.h"

namespace Catan {

	class AnimateSprite : public AnimateEntity, public DrawableEntity
	{
	public:

		void						draw(sf::RenderWindow& _window);
		void						update(sf::Time _time);

		void						addDelay(sf::Time _delay);
		void						addFrame(sf::IntRect _rect);

		void						nextFrame();
		void						nextDelay();

		AnimateSprite(Textures::Name _texName) : AnimateEntity(), DrawableEntity() {
			textureName = _texName;
			currentFrameTime = sf::Time::Zero;
			currentFrame = 0;
			currentDelay = 0;
		};
		~AnimateSprite();

	protected:
		sf::Texture&				getTexture();

	protected:
		std::vector<sf::Time>		delays;
		std::vector<sf::IntRect>	frames;

		int							currentDelay;
		int							currentFrame;
		sf::Time					currentFrameTime;

	private:
		Textures::Name		textureName;
	};

}