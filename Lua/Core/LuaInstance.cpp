#include "LuaInstance.h"

LuaInstance::LuaInstance()
{
	State = std::make_unique<LuaState>();
	luaL_openlibs(*State);
}