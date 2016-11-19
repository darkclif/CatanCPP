#pragma once
#include <SFML/Graphics.hpp>

namespace Catan {

	void setOriginAtCenter(sf::Sprite& _sprite) {
		sf::FloatRect lRect = _sprite.getLocalBounds();
		sf::Vector2f lOrig(lRect.width / 2.f, lRect.height / 2.f);
		_sprite.setOrigin(lOrig);
	}

	void setOriginAtCenter(sf::Text& _text) {
		sf::FloatRect lRect = _text.getLocalBounds();
		sf::Vector2f lOrig(lRect.width / 2.f, lRect.height / 2.f);
		_text.setOrigin(lOrig);
	}

}