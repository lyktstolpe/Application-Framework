#ifndef INVOKER_H
#define INVOKER_H
#pragma once

#include <deque>
#include <memory>

#include "Command.h"

class Invoker
{
private:
	std::unique_ptr<std::deque<std::shared_ptr<ICommand>>> _commandqueue;

public:
	Invoker();

	void submit_command(std::shared_ptr<ICommand> command);
	void flush_queue();
};

#endif