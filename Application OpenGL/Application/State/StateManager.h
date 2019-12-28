#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#pragma once

#include <memory>
#include <vector>

#include <loguru.hpp>

#include "ApplicationState.h"

class StateManager
{
public:
	StateManager();

	void change_state(IApplicationState* state);
	void push_state(IApplicationState* state);
	void pop_state();
	void clear();
	IApplicationState* get_current() { return _stack.back(); }

private:
	std::vector<IApplicationState*> _stack;
};

#endif