#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

#include "MyApplication.h"

int main()
{
	std::shared_ptr<MyApplication> a = std::make_shared<MyApplication>();

	a->init();
	a->run();

	return 0;
}