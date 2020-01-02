#pragma once

#include "Invoker_Vector.h"
#include "Invoker_Action.h"

class VectorAction : public Vector, public Action
{
public:
	VectorAction(std::unique_ptr<Command::Command> command, Bounds2D bounds)
		: Invoker(std::move(command))
		, Vector(std::move(command), bounds)
		, Action(std::move(command))
		, _bounds(bounds)
	{}

	~VectorAction() {}

	void attempt_execute()
	{
		Action::attempt_execute();
	}

	void activate(glm::vec2 val)
	{
		Vector::activate(val);
	}

	void activate() {}
	void activate(double val) {}

private:
	Bounds2D _bounds;
};