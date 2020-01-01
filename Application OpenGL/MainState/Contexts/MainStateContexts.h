#pragma once

#include <memory>

#include "../../Application/Application.h"

class Bound : public Context_cursor_enabled
{
public:
	Bound() {}
	~Bound() {}

	void init();
	void cleanup() {}
};

class Unbound : public Context_cursor_disabled
{
public:
	Unbound() {}
	~Unbound() {}

	void init();
	void cleanup() {}
};