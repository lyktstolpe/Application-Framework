#pragma once

#include "Invoker_Vector.h"
#include "Invoker_State.h"

class VectorState : public Vector, public State
{
public:
	VectorState(std::unique_ptr<Command::Command> command, Bounds2D bounds)
		: Invoker(std::move(command))
		, Vector(std::move(command), bounds)
		, State(std::move(command))
		, _bounds(bounds)
	{}

	~VectorState() {}

	void activate(glm::vec2 val)
	{
		Vector::activate(val);
	}

	void activate() {}
	void activate(double val) {}

private:
	Bounds2D _bounds;
};