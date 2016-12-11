#pragma once
#include <memory>

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>

#include "States.h"

class StateManager;

class State
{
public:
	struct Context {
		sf::RenderWindow*	window;
	};

	typedef std::unique_ptr<State> Ptr;

	virtual bool HandleEvents( sf::Event _event) = 0;
	virtual bool Update( sf::Time _dt) = 0;
	virtual void Draw( sf::RenderWindow& _window) = 0;

	virtual void resizeContent() = 0;

	bool isTransparent();
	void setTransparency(bool _trans);

	State(StateManager* _manager, Context _context);
	virtual ~State();
protected:
	void requestStackPush(States::ID _id);
	void requestStackPop();
	void requestStackClear();

	Context context;
private:
	StateManager* stateManager;
	bool transparent;
};

