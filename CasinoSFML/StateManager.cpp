#include "StateManager.h"
#include "Console.h"

namespace Catan {

	StateManager::StateManager(State::Context _context)
	{
		context = _context;
	}


	StateManager::~StateManager()
	{
	}

	void StateManager::Update(sf::Time _dt)
	{
		for (auto it = stack.rbegin(); it != stack.rend(); it++) {
			if ((*it)->Update(_dt))
				break;
		}
	}

	void StateManager::Draw(sf::RenderWindow& _window)
	{
		_window.clear();

		std::vector<State::Ptr>::iterator first_it = stack.begin();
		for (auto it = stack.begin(); it != stack.end(); it++) {
			if (!(*it)->isTransparent())
				first_it = it;
		}

		for (auto it = first_it; it != stack.end(); it++) {
			(*it)->Draw(_window);
		}

		_window.display();
	}

	void StateManager::handleEvent(sf::Event _event)
	{
		handleEngineEvent(_event);

		for (auto it = stack.rbegin(); it != stack.rend(); it++) {
			if ((*it)->HandleEvents(_event))
				break;
		}

		applyPendingChanges();
	}

	void StateManager::pushState(States::ID _id)
	{
		stack.push_back(createState(_id));
	}

	void StateManager::popState()
	{
		stack.pop_back();
	}

	void StateManager::clearStates()
	{
		stack.clear();

	}

	void StateManager::requestStackPush(States::ID _id)
	{
		pendingList.push_back(PendingChange(Action::Push, _id));
	}

	void StateManager::requestStackPop()
	{
		pendingList.push_back(PendingChange(Action::Pop));
	}

	void StateManager::requestStackClear()
	{
		pendingList.push_back(PendingChange(Action::Clear));
	}

	bool StateManager::isEmpty() const
	{
		return stack.empty();
	}

	State::Ptr StateManager::createState(States::ID _id)
	{
		auto found = stateFactory.find(_id);
		if (found == stateFactory.end()) {
			std::string lError = "State not found in stateFactory.";
			Console::debug << lError << std::endl;
			throw std::logic_error(lError);
		}

		return found->second();
	}

	void StateManager::applyPendingChanges()
	{

		for (auto it = pendingList.begin(); it != pendingList.end(); it++) {
			switch (it->action) {
			case StateManager::Action::Pop:		stack.pop_back(); break;
			case StateManager::Action::Push:	stack.push_back(createState(it->id)); break;
			case StateManager::Action::Clear:	stack.clear(); break;
			default: break;
			}
		}

		pendingList.clear();
	}

	void StateManager::handleEngineEvent(sf::Event _event)
	{
		if (_event.type == sf::Event::Resized) {
			for (auto it = stack.begin(); it != stack.end(); it++) {
				(*it)->resizeContent();
			}
		}
	}

}