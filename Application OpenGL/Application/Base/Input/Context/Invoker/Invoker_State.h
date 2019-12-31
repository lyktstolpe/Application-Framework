#pragma once

#include "Invoker_Base.h"

class State : public virtual Invoker
{
public:
	State(std::unique_ptr<ICommand> command)
		: Invoker(std::move(command))
	{}

	void activate()
	{
		_active = true;
	}

	void activate(double val) {}
	void activate(glm::vec2 val) {}
};