#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

#include "Application/Application.h"

int main()
{

	std::shared_ptr<Application> a = std::make_shared<Application>();

	a->run();

	return 0;
}