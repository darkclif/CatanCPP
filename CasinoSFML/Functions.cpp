#include "Functions.h"

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

	void setWindowAtCenter(sfg::Window::Ptr _window, sf::RenderWindow* _render) {
		sf::Vector2i lVect = _render->mapCoordsToPixel(sf::Vector2f(0, 0));
		sf::FloatRect winRect = _window->GetAllocation();
		_window->SetAllocation(sf::FloatRect(lVect.x - winRect.width / 2.f, lVect.y - winRect.height / 2.f, winRect.width, winRect.height));
	}

	void setViewOrigin(sf::RenderWindow * _window, sf::Vector2f _vect)
	{
		sf::View lView = _window->getView();
		lView.setCenter(_vect);
		_window->setView(lView);
	}

	void moveView(sf::RenderWindow* _window, sf::Vector2f _vect) {
		sf::View lView = _window->getView();
		lView.setCenter(lView.getCenter() + _vect);
		_window->setView(lView);
	}
}