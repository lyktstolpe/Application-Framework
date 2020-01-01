#include "Application_Base.h"
#include <loguru.cpp>

Application::Application()
	: _printnextfps(0)
	, _flag_change_state(-1)
{}

void Application::init()
{
	init_logging();
	init_glew();
	init_glfw();
	init_inputhandler();
	init_window();
	init_statemanager();
	init_states();
	LOG_F(INFO, "");
}

void Application::run()
{
	std::unique_ptr<Timer> timer = std::make_unique<Timer>();
	double t = 1.f;
	int frames = 0;
	double prevtime = 0.0,
		   currtime = 0.0;

	while (!_window->is_closed())
	{
		update();
		
		frames++;
		currtime = timer->elapsed();
		// LOG_F(INFO, "Frametime: %f", currtime - prevtime);
		prevtime = currtime;

		if (currtime > t)
		{
			if (_printnextfps)
			{
				LOG_F(INFO, "%i fps", frames);
				_printnextfps = false;
			}
			t = floor(timer->elapsed() + 1.f);
			frames = 0;
		}

		if (_flag_change_state != -1)
		{
			_statemanager->change_state(_states[_flag_change_state].get());
			_flag_change_state = -1;
		}
 	}
}

void Application::update()
{
	glfwPollEvents();
	_statemanager->get_events();
	_statemanager->update();
	_statemanager->display();
	_window->update();
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
	_window = std::make_unique<Window>(720, 480, _inputhandler.get());
}

void Application::init_statemanager()
{
	_statemanager = std::make_unique<StateManager>();
}