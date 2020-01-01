#pragma once

#include "Invoker_Base.h"

class Scalar : public virtual Invoker
{
public:
	Scalar(std::unique_ptr<Command::ICommand> command, Bounds1D bounds)
		: Invoker(std::move(command))
		, _bounds(bounds)
	{}

	virtual ~Scalar() {}

	void activate(double val)
	{
		_active = val <= _bounds.upper && val >= _bounds.lower;
	}

	void activate() {}
	void activate(glm::vec2 val) {}

protected:
	Bounds1D _bounds;
};