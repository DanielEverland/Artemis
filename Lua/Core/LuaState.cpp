// Invisible Walls is the sole owner of all rights of, and to the video game First Class Trouble and affiliated projects and retains all rights to concepts and ideas from First Class Trouble, which are not transferred herein, and retains all common law copyrights and trademarks to the given title.
#include "LuaState.h"

LuaState::LuaState()
{
	RawState = lua_open();
}

LuaState::~LuaState()
{
	lua_close(RawState);
}

LuaState::operator lua_State*() const
{
	return RawState;
}
