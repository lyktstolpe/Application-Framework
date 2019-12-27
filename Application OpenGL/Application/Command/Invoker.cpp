#include "Invoker.h"

Invoker::Invoker()
{
	_commandqueue = std::make_unique<std::deque<std::shared_ptr<ICommand>>>();
}

void Invoker::submit_command(std::shared_ptr<ICommand> command)
{
	_commandqueue->push_back(command);
}

void Invoker::flush_queue()
{
	while (!_commandqueue->empty())
	{
		_commandqueue.get()->at(0)->execute();
		_commandqueue->pop_front();
	}
}
