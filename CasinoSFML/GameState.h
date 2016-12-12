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
	const float MOVE_SPEED = 500.0f;

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

	void resizeContent();

	GameState(StateManager* _engine, Context _context);
	~GameState();

public:
	void exitGame();

private:
	void spawnGUI();

	/* Navigation */
	bool						isActionKeyPressed(ActionKey _key);
	void						changeActionKeyState(ActionKey _key, bool _state);

private:
	std::unique_ptr<Map>		map;
	std::unique_ptr<Game>		game;

	std::unique_ptr<PlayerGUI>	playerGUI;

	sfg::SFGUI					sfg_sfgui;
	sfg::Desktop				sfg_desktop;

	/* Navigation */
	std::vector<bool>			actionKeysStates;
};

