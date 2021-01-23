// Invisible Walls is the sole owner of all rights of, and to the video game First Class Trouble and affiliated projects and retains all rights to concepts and ideas from First Class Trouble, which are not transferred herein, and retains all common law copyrights and trademarks to the given title.
#include "LuaState.h"

#include <exception>

std::unique_ptr<LuaState> LuaState::CreateFromFile(const std::string& filePath)
{
	auto newState = std::make_unique<LuaState>();

	luaL_dofile(*newState, filePath.c_str());

	return newState;
}

std::unique_ptr<LuaState> LuaState::CreateFromString(const std::string& rawString)
{
	auto newState = std::make_unique<LuaState>();
	
	int result = luaL_loadstring(*newState, rawString.c_str());
	if(result != 0)
	{
		throw std::exception();
	}

	return newState;
}

LuaState::LuaState() : RawState(luaL_newstate(), lua_close)
{
}

LuaState::operator lua_State*() const
{
	return RawState.get();
}
