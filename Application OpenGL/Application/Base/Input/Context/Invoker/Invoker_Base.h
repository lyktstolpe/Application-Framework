#pragma once

#include <memory>

#include <glm/vec2.hpp>

#include "../../../Command/Command.h"

struct Bounds1D
{
	double lower;
	double upper;
};

struct Bounds2D
{
	glm::vec2 lower;
	glm::vec2 upper;
};

class Invoker
{
public:
	Invoker() 
		: _command(nullptr)
		, _active(false)
	{}
	Invoker(std::unique_ptr<ICommand> command)
		: _command(std::move(command))
		, _active(false)
	{}

	virtual ~Invoker() {}

	virtual void attempt_execute()
	{
		if (_active && _command)
			_command->execute();
	}

	virtual void activate() = 0;
	virtual void activate(double val) = 0;
	virtual void activate(glm::vec2 val) = 0;

	void deactivate()
	{
		_active = false;
	}

protected:
	std::unique_ptr<ICommand> _command;
	bool _active;
};
