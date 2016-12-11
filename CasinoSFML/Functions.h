#pragma once
#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

namespace Catan {

	void setOriginAtCenter(sf::Sprite& _sprite);
	void setOriginAtCenter(sf::Text& _text);

	// SFGUI
	void setWindowAtCenter(sfg::Window::Ptr _window, sf::RenderWindow* _render);

	// SFML
	void setViewOrigin(sf::RenderWindow* _window, sf::Vector2f _vect);
	void moveView(sf::RenderWindow* _window, sf::Vector2f _vect);
	void zoomView(sf::RenderWindow* _window, float _zoom);

}