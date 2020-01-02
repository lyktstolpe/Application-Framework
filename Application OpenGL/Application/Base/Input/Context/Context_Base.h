#pragma once

#include <array>
#include <memory>
#include <vector>

#include <GLFW/glfw3.h>

#include "../../Event/InputEvent.h"
#include "Invoker/Invoker.h"

class ApplicationState;
class Application;

class Context
{
friend class ApplicationState;

public:
	Context();
	virtual ~Context() {}

	void handle_key_events(std::unique_ptr<std::vector<KeyEvent>>& events);
	virtual void cleanup_core();
	virtual void init_core() = 0;
	virtual void handle_mouse_events(std::unique_ptr<std::vector<MouseEvent>>& events) = 0;
	virtual void attempt_invoke() = 0;

	// Function wrappers
	template<class inputtype, class cmd, typename ...Args>
	void map_key(int key, Args ...args)
	{
		_keymap[key] = std::make_unique<inputtype>(std::move(std::make_unique<cmd>(std::forward<Args>(args)...)));
	}

	template<class inputtype>
	void map_key(int key, std::unique_ptr<Command::Command> cmd)
	{
		_keymap[key] = std::make_unique<inputtype>(std::move(cmd));
	}

	std::unique_ptr<Command::ChangeState> get_command_change_to_state(int i);
	std::unique_ptr<Command::ChangeContext> get_command_change_to_context(int i);

protected:
	std::array<std::unique_ptr<Invoker>, GLFW_KEY_LAST + 1> _keymap;
	std::weak_ptr<GLFWwindow> _glfwwindow;
	std::weak_ptr<Application> _parentapplication;
	ApplicationState* _parentstate;

	virtual void init() = 0;
	virtual void cleanup() = 0;
};