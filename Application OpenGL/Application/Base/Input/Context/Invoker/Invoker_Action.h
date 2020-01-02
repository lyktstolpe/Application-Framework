#pragma once

#include "Invoker_Base.h"

class Action : public virtual Invoker
{
public:
	Action(std::unique_ptr<Command::Command> command)
		: Invoker(std::move(command))
	{}

	virtual ~Action() {}

	void attempt_execute()
	{
		if (_active && _command)
		{
			_command->execute();
			deactivate();
		}
	}

	void activate()
	{
		_active = true;
	}

	void activate(double val) {}
	void activate(glm::vec2 val) {}
};