#include "MainStateContexts.h"

MainContextMain::MainContextMain()
{
	map_key<Action, Print>(GLFW_KEY_A, "State::main \tContext::first   \tA pressed.");
}

MainContextSecond::MainContextSecond()
{
	map_key<State, Print>(GLFW_KEY_S, "State::main \tContext::second \tS pressed.");
	map_mouse<Action, Print>(GLFW_MOUSE_BUTTON_LEFT, "State::main \tContext::second \tLeft mouse pressed.");
}