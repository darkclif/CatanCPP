
// Pinky
// 2016

#include <SFML/Graphics.hpp>

#include "Map.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 800), "SFML works!");
	window.setFramerateLimit(30);

	Map lMap;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		//Draw
		lMap.Show(window, 400.0, 600.0);

		window.display();
	}

	return 0;
}