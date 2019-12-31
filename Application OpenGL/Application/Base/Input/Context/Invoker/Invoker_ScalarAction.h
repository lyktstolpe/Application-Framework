#pragma once

#include "Invoker_Scalar.h"
#include "Invoker_Action.h"

class ScalarAction : public Scalar, public Action
{
public:
	ScalarAction(std::unique_ptr<ICommand> command, Bounds1D bounds)
		: Invoker(std::move(command))
		, Scalar(std::move(command), bounds)
		, Action(std::move(command))
	{}

	void attempt_execute()
	{
		Action::attempt_execute();
	}

	void activate(double val)
	{
		Scalar::activate(val);
	}

	void activate() {}
	void activate(glm::vec2 val) {}
};