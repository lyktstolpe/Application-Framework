#include "Application.h"
#include <loguru.cpp>

Application::Application()
	: _states(new std::shared_ptr<IApplicationState>[size_t(State::count)], std::default_delete<std::shared_ptr<IApplicationState>[]>())
	, _printnextfps(0)
{
	init_logging();
	init_glew();
	init_glfw();
	init_window();
	init_statemanager();
	init_states();
}

void Application::run()
{
	init_key_bindings(); // Contains shared_from_this() and cannot be called from constructor

	std::unique_ptr<Timer> timer = std::make_unique<Timer>();
	double t = 1.f;
	int frames = 0;

	while (!_window->is_closed())
	{
		_statemanager->update_current();
		_statemanager->display_current();
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

void Application::init_window()
{
	_window = std::make_unique<Window>();
}

void Application::init_statemanager()
{
	_statemanager = std::make_shared<StateManager>();
}

void Application::init_states()
{
	std::shared_ptr<std::shared_ptr<ICommand>[size_t(State::count)]> changestatecommands(new
		std::shared_ptr<ICommand>[size_t(State::count)],
		std::default_delete<std::shared_ptr<ICommand>[]>() 
	);

	StateInfo createinfo_state;
	createinfo_state.changestatecommands = changestatecommands;
	createinfo_state.inputhandler = _window->inputhandler();

	// States
	_states[size_t(State::main)] = std::make_shared<MainState>(&createinfo_state);
	_states[size_t(State::extra)] = std::make_shared<ExtraState>(&createinfo_state);

	// Commands
	changestatecommands[size_t(State::main)] = std::make_shared<AppCmdChangeState>(_statemanager, _states[size_t(State::main)]);
	changestatecommands[size_t(State::extra)] = std::make_shared<AppCmdChangeState>(_statemanager, _states[size_t(State::extra)]);

	_statemanager->change_state(_states[size_t(State::main)]);
}

void Application::init_key_bindings()
{
	std::unique_ptr<ICommand> printfps = std::make_unique<AppCmdPrintFps>(shared_from_this());
	_window->inputhandler()->map_key_const(GLFW_KEY_F1, std::move(printfps));
}
