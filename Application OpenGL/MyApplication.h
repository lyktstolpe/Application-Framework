#pragma once

#include "Application/Application.h"
#include "MainState/MainState.h"
#include "SecondState/SecondState.h"

class MyApplication : public Application
{
public:
	MyApplication()
	{}

	void init_states()
	{
		create_state<MainState>();
		create_state<SecondState>();

		change_to_state(0);
	}
};