#pragma once

#include "LuaCore.h"

class LuaInstance
{
public:
	LuaInstance();

private:
	unique_ptr<LuaState> State;
};