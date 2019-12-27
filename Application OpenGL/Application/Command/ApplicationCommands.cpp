#include "ApplicationCommands.h"
#include "../Application.h"

AppCmdChangeState::AppCmdChangeState(std::shared_ptr<StateManager> statemanager, std::shared_ptr<IApplicationState> state)
{
	_statemanager = statemanager;
	_state = state;
}

void AppCmdChangeState::execute() {
	_statemanager->change_state(_state);
}

AppCmdPrintFps::AppCmdPrintFps(std::shared_ptr<Application> application)
{
	_application = application;
}

void AppCmdPrintFps::execute() {
	_application->printfps();
}