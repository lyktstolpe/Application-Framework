#pragma once

#include "Invoker_Base.h"

class State : public virtual Invoker
{
public:
	State(std::unique_ptr<Command::Command> command)
		: Invoker(std::move(command))
	{}

	virtual ~State() {}

	void activate()
	{
		_active = true;
	}

	void activate(double val) {}
	void activate(glm::vec2 val) {}
};