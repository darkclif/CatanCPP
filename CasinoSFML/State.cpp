#include "State.h"
#include "StateManager.h"

bool State::isTransparent()
{
	return transparent;
}

void State::setTransparency(bool _trans)
{
	transparent = _trans;
}

State::State(StateManager * _manager, Context _context)
{
	stateManager = _manager;
	context = _context;
}

State::~State()
{
}

void State::requestStackPush(States::ID _id)
{
	stateManager->requestStackPush(_id);
}

void State::requestStackPop()
{
	stateManager->requestStackPop();
}

void State::requestStackClear()
{
	stateManager->requestStackClear();
}
