#pragma once

#include <loguru.hpp>

#include "../Application/Application.h"
#include "Contexts/SecondStateContexts.h"

class SecondState : public ApplicationState
{
public:
	SecondState() {}
	~SecondState() {}

	void init();
	void cleanup();
	void pause();
	void resume();
	void get_events();
	void update();
	void display();

	const char* get_name() { return "second"; }
};
