#pragma once

#include <memory>
#include <vector>

#include <loguru.hpp>

#include "ApplicationState.h"

class StateManager
{
public:
	StateManager();
	~StateManager() {}

	void get_events();
	void update();
	void display();
	void change_state(ApplicationState* state);
	void push_state(ApplicationState* state);
	void pop_state();
	void clear();
	ApplicationState* get_current() { return _stack.back(); }

private:
	std::vector<ApplicationState*> _stack;
};

