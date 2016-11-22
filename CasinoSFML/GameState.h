#pragma once
#include "State.h"
#include "Map.h"
#include "Game.h"

#include "SFGUI/SFGUI.hpp"
#include "SFGUI/Widgets.hpp"

class GameState : public State
{
public:
	bool HandleEvents(sf::Event _event);
	bool Update(sf::Time _dt);
	void Draw(sf::RenderWindow& _window);

	GameState(StateManager* _engine, Context _context);
	~GameState();

public:
	void exitGame();

private:
	void spawnGUI();

private:
	std::unique_ptr<Map>	map;
	std::unique_ptr<Game>	game;

	sfg::SFGUI sfg_sfgui;
	sfg::Desktop sfg_dektop;

	// GUI
	sfg::Label::Ptr labInfo;
};

