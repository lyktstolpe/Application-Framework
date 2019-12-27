#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#pragma once

#include <memory>
#include <vector>

#include <loguru.hpp>

#include "State.h"

class StateManager
{
public:
	StateManager();

	void change_state(std::shared_ptr<IApplicationState> state);
	void push_state(std::shared_ptr<IApplicationState> state);
	void pop_state();
	void clear();
	void update_current();
	void display_current();

private:
	std::vector<std::shared_ptr<IApplicationState>> _stack;
};

#endif