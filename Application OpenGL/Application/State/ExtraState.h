#ifndef EXTRASTATE_H
#define EXTRASTATE_H

#pragma once

#include <loguru.hpp>

#include "State.h"
#include "../Command/ApplicationCommands.h"

class ExtraState : public IApplicationState
{
public:
	ExtraState() {}
	ExtraState(StateInfo* createinfo);

	void init();
	void cleanup();
	void pause();
	void resume();
	void get_events();
	void update();
	void display();

	const char* get_name() { return "extra"; }
};

#endif