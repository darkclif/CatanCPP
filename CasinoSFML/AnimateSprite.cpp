#include "AnimateSprite.h"
#include "Console.h"

namespace Catan {

	void AnimateSprite::draw(sf::RenderWindow & _window)
	{
		if (frames.empty())
			return;

		setTexture(getTexture());
		setTextureRect(frames[currentFrame]);
		_window.draw(getSprite());
	}

	void AnimateSprite::update(sf::Time _time)
	{
		if (frames.empty() || delays.empty() || !isRunning())
			return;

		currentFrameTime += _time;

		while (currentFrameTime > delays[currentDelay]) {
			currentFrameTime -= delays[currentDelay];
			nextFrame();
			nextDelay();
		}
	}

	void AnimateSprite::addDelay(sf::Time _delay)
	{
		delays.push_back(_delay);
	}

	void AnimateSprite::addFrame(sf::IntRect _rect)
	{
		frames.push_back(_rect);
	}

	void AnimateSprite::nextFrame()
	{
		currentFrame++;
		currentFrame %= frames.size();
	}

	void AnimateSprite::nextDelay()
	{
		currentDelay++;
		currentDelay %= delays.size();
	}

	AnimateSprite::~AnimateSprite()
	{
	}

	sf::Texture & AnimateSprite::getTexture()
	{
		return ResourceManager::getInstance().getTexture(textureName);
	}

}