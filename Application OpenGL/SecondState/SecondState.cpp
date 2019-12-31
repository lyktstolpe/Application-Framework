#include "SecondState.h"

void SecondState::init()
{
	create_context<SecondBound>();
	create_context<SecondUnbound>();
	change_context(1);
}

void SecondState::cleanup()
{

}

void SecondState::pause()
{

}

void SecondState::resume()
{

}

void SecondState::get_events()
{

}

void SecondState::update()
{
}

void SecondState::display()
{

}