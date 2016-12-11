#pragma once
#include <SFML/Graphics.hpp>

#include <functional>

#include "States.h"
#include "State.h"

class StateManager
{
public:
	enum Action {
		Push,
		Pop,
		Clear
	};

public:
	StateManager( State::Context _context);
	~StateManager();

	template<typename T>
	void registerState(States::ID _id) {
		stateFactory[_id] = [this]() {
			return State::Ptr( new T(this, context));
		};
	}

	void Update(sf::Time _dt);
	void Draw(sf::RenderWindow& _window);
	void handleEvent(sf::Event _event);

	void pushState( States::ID _id);
	void popState();
	void clearStates();

	void requestStackPush(States::ID _id);
	void requestStackPop();
	void requestStackClear();
	
	bool isEmpty() const;

private:
	State::Ptr createState(States::ID _id);
	void applyPendingChanges();

	void handleEngineEvent(sf::Event _event);

private:
	struct PendingChange {
		PendingChange( Action _action, States::ID _id) : action{ _action }, id{_id} {};
		PendingChange( Action _action) : action{ _action }{};
		Action action;
		States::ID id;
	};

private:
	State::Context context;

	std::vector<State::Ptr> stack;
	std::vector<PendingChange> pendingList;

	std::map<States::ID, std::function<State::Ptr()>> stateFactory;
};

