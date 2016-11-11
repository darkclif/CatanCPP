
// Pinky
// 2016

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "ResourceManager.h"

#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 800), "SFML works!");
	window.setFramerateLimit(30);

	Map lMap;
	bool draw = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				

				sf::View lView = window.getView();

				switch (event.key.code) {
					case sf::Keyboard::Left: lView.move(sf::Vector2f(-10, 0)); break;
					case sf::Keyboard::Up: lView.move(sf::Vector2f(0, -10)); break;
					case sf::Keyboard::Right: lView.move(sf::Vector2f(10, 0)); break;
					case sf::Keyboard::Down: lView.move(sf::Vector2f(0, 10)); break;
					case sf::Keyboard::A: lView.zoom((float)0.99); break;
					case sf::Keyboard::S: draw = ( draw ? false : true ); break;
					default: break;
				}

				window.setView(lView);
			}
		}

		window.clear();

		//Draw
		if (draw) lMap.Show(window, 400.0, 600.0);

		window.display();
	}

	return 0;
}