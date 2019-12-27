#include "StateManager.h"

StateManager::StateManager()
	: _stack()
{}

void StateManager::change_state(std::shared_ptr<IApplicationState> state)
{
	if (!state)
	{
		LOG_F(WARNING, "Tried to change to non-existent state.");
		return;
	}

	LOG_F(INFO, "Changing to State::%s", state->get_name());
	if (!_stack.empty())
	{
		_stack.back()->cleanup();
		_stack.pop_back();
	}

	_stack.push_back(state);
	_stack.back()->init();
}

void StateManager::push_state(std::shared_ptr<IApplicationState> state)
{
	if (!state)
	{
		LOG_F(WARNING, "Tried to push non-existent state.");
		return;
	}

	if (!_stack.empty())
		_stack.back()->pause();
	
	_stack.push_back(state);
	_stack.back()->init();	
}

void StateManager::pop_state()
{
	if (!_stack.empty())
	{
		_stack.back()->cleanup();
		_stack.pop_back();
	}

	if (!_stack.empty())
		_stack.back()->resume();
}

void StateManager::clear()
{
	while (!_stack.empty())
	{
		_stack.back()->cleanup();
		_stack.pop_back();
	}
}

void StateManager::update_current()
{
	if (!_stack.empty())
		_stack.back()->update();
}

void StateManager::display_current()
{
	if (!_stack.empty())
	{
		// _stack.back()->printinfo();
		_stack.back()->display();
	}
}
