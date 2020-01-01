#pragma once

#include "Invoker_Base.h"

class Vector : public virtual Invoker
{
public:
	Vector(std::unique_ptr<Command::ICommand> command, Bounds2D bounds)
		: Invoker(std::move(command))
		, _bounds(bounds)
	{}

	virtual ~Vector() {}

	void activate(glm::vec2 val)
	{
		_active = val.x <= _bounds.upper.x && val.y <= _bounds.upper.y &&
				  val.x >= _bounds.lower.x && val.y >= _bounds.lower.y;
	}

	void activate() {}
	void activate(double val) {}

protected:
	Bounds2D _bounds;
};