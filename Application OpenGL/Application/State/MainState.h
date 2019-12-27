#ifndef MAINSTATE_H
#define MAINSTATE_H

#pragma once

#include <loguru.hpp>

#include "State.h"
#include "../Command/ApplicationCommands.h"

class MainState : public IApplicationState
{
public:
	MainState() {}
	MainState(StateInfo* createinfo);

	void init();
	void cleanup();
	void pause();
	void resume();
	void get_events();
	void update();
	void display();

	const char* get_name() { return "main"; }
};

#endif