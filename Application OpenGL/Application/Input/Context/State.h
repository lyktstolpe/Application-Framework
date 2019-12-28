#pragma once

#include <memory>

#include "InputType.h"

	class State : public InputTypeKey
	{
	public:
		State(std::unique_ptr<ICommand> command)
			: InputTypeKey(std::move(command))
		{}
	
		void attempt_execute() {
			if (_active)
				_command->execute();
		}
	
		void activate() {
			_active = true;
		}

		void deactivate() {
			_active = false;
		}
	};
