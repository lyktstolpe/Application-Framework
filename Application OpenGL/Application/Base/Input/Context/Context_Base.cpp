#include "Context.h"
#include "Context_Base.h"
#include "../../Application_Base.h"

Context::Context()
{}

void Context::handle_key_events(std::unique_ptr<std::vector<KeyEvent>>& events)
{
	for (int i = int(events->size()) - 1; i >= 0; --i)
	{
		int key = events->at(i).key;
		if (!_keymap[key])
			continue;
		KeyEventType type = events->at(i).type;

		if (type == KeyEventType::key_pressed)
			_keymap[key]->activate();
		if (type == KeyEventType::key_released)
			_keymap[key]->deactivate();

		events->erase(events->begin() + i);
	}
}

void Context::cleanup_core()
{
	for (auto& invoker : _keymap)
		if (invoker)
			invoker.reset(nullptr);
	cleanup();
}

std::unique_ptr<Command::ChangeState> Context::get_command_change_to_state(int i)
{
	auto parentapp_shared = _parentapplication.lock();
	std::unique_ptr<Command::ChangeState> cmd = parentapp_shared->get_command_change_to_state(i);
	return std::move(cmd);
}

std::unique_ptr<Command::ChangeContext> Context::get_command_change_to_context(int i)
{
	std::unique_ptr<Command::ChangeContext> cmd = _parentstate->get_command_change_to_context(i);
	return std::move(cmd);
}
