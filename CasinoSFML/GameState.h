#pragma once
#include "State.h"
#include "Map.h"
#include "Game.h"
#include "PlayerGUI.h"

#include "SFGUI/SFGUI.hpp"
#include "SFGUI/Widgets.hpp"

class GameState : public State
{
public:
	enum ActionKey : int{
		ZOOM_IN,
		ZOOM_OUT,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		_SIZE
	};

	bool HandleEvents(sf::Event _event);
	bool Update(sf::Time _dt);
	void Draw(sf::RenderWindow& _window);

	void						resizeContent();

	GameState(StateManager* _engine, Context _context);
	~GameState();

public:
	void exitGame();

private:
	void spawnGUI();

private:
	std::unique_ptr<Map>		map;
	std::unique_ptr<Game>		game;

	sfg::SFGUI					sfg_sfgui;
	sfg::Desktop				sfg_desktop;

	std::unique_ptr<PlayerGUI>	playerGUI;

	bool						isActionKeyPressed(ActionKey _key);
	void						changeActionKeyState(ActionKey _key, bool _state);
	std::vector<bool>			actionKeysStates;

	// GUI
	sfg::Label::Ptr labInfo;
};

