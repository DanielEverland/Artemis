#pragma once

#include <memory>

#include "LuaState.h"

class GlobalState
{
public:
	GlobalState();

	operator LuaState*() const;

private:
	std::unique_ptr<LuaState> State;
};