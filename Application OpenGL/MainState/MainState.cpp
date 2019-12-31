#include "MainState.h"

void MainState::init()
{
	create_context<Bound>();
	create_context<Unbound>();
	change_context(0);
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