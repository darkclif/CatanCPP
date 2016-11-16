// Pinky
// 2016
#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include "Tile.h"
#include "Map.h"
#include "ResourceManager.h"
#include "Console.h"
#include <iostream>

int main() {

	
	// Create a window and add the box layouter to it. Also set the window's title.
	sfg::SFGUI m_sfgui;
	
	auto sf_window = sfg::Window::Create();
	sf_window->SetTitle("Hello world!");

	// Create a desktop and add the window to it.
	sfg::Desktop desktop;
	desktop.Add(sf_window);

	std::srand(unsigned(std::time(0)));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1300, 1000), "SFML works!", sf::Style::Default,settings);
	window.setFramerateLimit(30);

	// We're not using SFML to render anything in this program, so reset OpenGL
	// states. Otherwise we wouldn't see anything.
	window.resetGLStates();

	sf::Clock clock;

	Map lMap(&window);
	bool draw = true;

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			desktop.HandleEvent(event);

			if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				int x = event.mouseButton.x;
				int y = event.mouseButton.y;

				sf::Vector2f vect = window.mapPixelToCoords(sf::Vector2i(x, y));

				for (auto& lRoad : lMap.Roads) {
					if (lRoad->isPointInEntity(vect))
						lRoad->color = sf::Color::Red;
				}
			}

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
				case sf::Keyboard::S: lView.zoom((float)1.01); break;
				default: break;
				}

				window.setView(lView);
			}
		}

		// Update SFGUI with elapsed seconds since last call.
		desktop.Update(clock.restart().asSeconds());

		window.clear();

		//Draw
		lMap.Show(window);
		m_sfgui.Display(window);

		window.display();
	}

	return 0;
}