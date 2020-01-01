#pragma once

#include <memory>

#include "../../Application/Application.h"

class SecondBound : public Context_cursor_enabled
{
public:
	SecondBound() {}
	~SecondBound() {}

	void init();
	void cleanup() {}
};

class SecondUnbound : public Context_cursor_disabled
{
public:
	SecondUnbound() {}
	~SecondUnbound() {}

	void init();
	void cleanup() {}
};