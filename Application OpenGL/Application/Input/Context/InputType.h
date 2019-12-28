#pragma once

#include <memory>

#include "../../Command/Command.h"
#include "../../Event/InputEvent.h"

	class InputTypeKey
	{
	public:
		InputTypeKey() 
			: _command(nullptr)
			, _active(0)
		{}
		InputTypeKey(std::unique_ptr<ICommand> command)
			: _command(std::move(command))
			, _active(0)
		{}

		virtual void attempt_execute() = 0;
		virtual void activate() = 0;
		virtual void deactivate() = 0;

	protected:
		std::unique_ptr<ICommand> _command;
		bool _active;
	};
