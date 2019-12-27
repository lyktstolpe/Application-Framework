#ifndef APPLICATIONCOMMAND_H
#define APPLICATIONCOMMAND_H

#pragma once

#include "Command.h"
#include "../State/State.h"
#include "../State/StateManager.h"

class Application;

class AppCmdChangeState : public ICommand
{
public:
	AppCmdChangeState(std::shared_ptr<StateManager> statemanager, std::shared_ptr<IApplicationState> state);
	void execute();
	ActivationType activation_type() { return ActivationType::press; }
	
private:
	std::shared_ptr<StateManager> _statemanager;
	std::shared_ptr<IApplicationState> _state;
};

class AppCmdPrintFps : public ICommand
{
public:
	AppCmdPrintFps(std::shared_ptr<Application> application);
	void execute();
	ActivationType activation_type() { return ActivationType::press; }

private:
	std::shared_ptr<Application> _application;
};

#endif