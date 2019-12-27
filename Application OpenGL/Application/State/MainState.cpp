#include "MainState.h"

MainState::MainState(StateInfo* createinfo) : IApplicationState(createinfo)
{
}

void MainState::init()
{
	// Change to State::extra
	_inputhandler->map_key(GLFW_KEY_LEFT_SHIFT, _changestatecommands[size_t(State::extra)]);
	
}

void MainState::cleanup()
{

}

void MainState::pause()
{

}

void MainState::resume()
{

}

void MainState::get_events()
{

}

void MainState::update()
{

}

void MainState::display()
{

}