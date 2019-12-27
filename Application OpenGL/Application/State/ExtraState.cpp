#include "ExtraState.h"

ExtraState::ExtraState(StateInfo* createinfo) : IApplicationState(createinfo)
{
}

void ExtraState::init()
{
	_inputhandler->map_key(GLFW_KEY_LEFT_SHIFT, _changestatecommands[size_t(State::main)]);
}

void ExtraState::cleanup()
{

}

void ExtraState::pause()
{

}

void ExtraState::resume()
{

}

void ExtraState::get_events()
{

}

void ExtraState::update()
{

}

void ExtraState::display()
{

}