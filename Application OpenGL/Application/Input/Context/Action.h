#pragma once

#include <memory>

#include "InputType.h"

	class Action : public InputTypeKey
	{
	public:
		Action(std::unique_ptr<ICommand> command)
			: InputTypeKey(std::move(command))
		{}

		void attempt_execute() {
			if (_active)
			{
				_command->execute();
				_active = false;
			}
		}

		void activate() {
			_active = true;
		}

		void deactivate() {}
	};
