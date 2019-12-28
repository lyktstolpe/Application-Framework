#include "Application.h"
#include <loguru.cpp>

Application::Application()
	: _printnextfps(0)
{
	init_logging();
	init_glew();
	init_glfw();
	init_inputhandler();
	init_window();
	init_statemanager();
	init_states();
}

void Application::run()
{
	// Set user pointer for all states to &this. shared_from_this cannot be called from constructor
	for (auto& s : _states)
		IApplicationState::set_userpointer<Application>(*s, shared_from_this());

	// Set active state to State::main
	_statemanager->change_state(_states[size_t(AppState::main)].get());

	std::unique_ptr<Timer> timer = std::make_unique<Timer>();
	double t = 1.f;
	int frames = 0;

	while (!_window->is_closed())
	{
		glfwPollEvents();
		_statemanager->get_current()->get_events();
		_statemanager->get_current()->update();
		_statemanager->get_current()->display();
		_window->update();
		
		frames++;
		if (timer->elapsed() > t)
		{
			if (_printnextfps)
			{
				LOG_F(INFO, "%i fps", frames);
				_printnextfps = false;
			}
			t = floor(timer->elapsed() + 1.f);
			frames = 0;
		}
 	}
}

void Application::init_logging()
{
	loguru::g_preamble_date = false;
	loguru::g_preamble_thread = false;
	loguru::g_preamble_file = false;
	loguru::g_preamble_verbose = false;
}

void Application::init_glew()
{
}

void Application::init_glfw()
{
	if (!glfwInit())
		LOG_F(ERROR, "Failed to initialize GLFW.");
}

void Application::init_inputhandler()
{
	_inputhandler = std::make_unique<InputHandler>();
}

void Application::init_window()
{
	_window = std::make_unique<Window>(_inputhandler.get());
}

void Application::init_statemanager()
{
	_statemanager = std::make_unique<StateManager>();
}

void Application::init_states()
{
	// States
	_states[size_t(AppState::main)] = std::make_unique<MainState>();
}