#ifndef MAINSTATE_H
#define MAINSTATE_H

#pragma once

#include <loguru.hpp>

#include "../State/ApplicationState.h"
#include "Contexts/MainStateContexts.h"

class MainState : public IApplicationState
{
public:
	MainState() {}

	void init();
	void cleanup();
	void pause();
	void resume();
	void get_events_append();
	void update_append();
	void display();

	const char* get_name() { return "main"; }
};

#endif