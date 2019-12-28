#include "MainState.h"
#include "../Application.h"

void MainState::init()
{
	LOG_F(INFO, "MainState::init()");
	_inputcontexts.push_back(std::move(std::make_unique<MainContextMain>()));
	_inputcontexts.push_back(std::move(std::make_unique<MainContextSecond>()));
	_contextmanager.change_context(_inputcontexts[0].get());
	_contextmanager.push_context(_inputcontexts[1].get());
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

void MainState::get_events_append()
{

}

void MainState::update_append()
{
}

void MainState::display()
{

}