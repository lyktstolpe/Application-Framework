#pragma once

#include "Invoker_Scalar.h"
#include "Invoker_State.h"

class ScalarState : public Scalar, public State
{
public:
	ScalarState(std::unique_ptr<ICommand> command, Bounds1D bounds)
		: Invoker(std::move(command))
		, Scalar(std::move(command), bounds)
		, State(std::move(command))
		, _bounds(bounds)
	{}

	void activate(double val)
	{
		Scalar::activate(val);
	}

	void activate() {}
	void activate(glm::vec2 val) {}

private:
	Bounds1D _bounds;
};