#pragma once
#include "State.h"
#include "Functions.h"

#include "Console.h"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include "AnimateSprite.h"

namespace Catan {

	class MainMenuState :
		public State
	{
	public:
		bool HandleEvents(sf::Event _event);
		bool Update(sf::Time _dt);
		void Draw(sf::RenderWindow& _window);

		void resizeContent();

		MainMenuState(StateManager* _engine, Context _context);
		~MainMenuState();

	private:
		void NewGame();
		void Exit();

		void spawnGUI();
		void spawnBackground();

	private:
		std::unique_ptr<AnimateSprite> sprite;

		sfg::SFGUI sfg_sfgui;
		sfg::Desktop sfg_dektop;
	};

}