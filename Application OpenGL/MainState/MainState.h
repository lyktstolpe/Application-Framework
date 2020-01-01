#ifndef MAINSTATE_H
#define MAINSTATE_H

#pragma once

#include <loguru.hpp>

#include "../Application/Application.h"
#include "Contexts/MainStateContexts.h"

class MainState : public IApplicationState
{
public:
	MainState() {}
	~MainState() {}

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