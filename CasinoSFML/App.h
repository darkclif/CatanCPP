#pragma once
#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "Tile.h"
#include "Map.h"
#include "ResourceManager.h"
#include "Console.h"
#include "State.h"

#include <iostream>

namespace Catan {

	class App
	{
	public:
		void Run();


		App();
		~App();
	private:

		void registerStates(StateManager& _engine);
		void handleGlobalEvent(sf::Event _event, State::Context _context, StateManager& _engine);
	};

}