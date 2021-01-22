#pragma once

#include <string>

#include "LuaCoreMinimal.h"

struct LuaState
{
public:
	static LuaState CreateFromFile(const std::string& filePath);
	static LuaState CreateFromString(const std::string& rawString);

	~LuaState();

	LuaState(const LuaState& other)
		: RawState(other.RawState)
	{
	}

	LuaState(LuaState&& other) noexcept
		: RawState(other.RawState)
	{
	}

	LuaState& operator=(const LuaState& other)
	{
		if (this == &other)
			return *this;
		RawState = other.RawState;
		return *this;
	}

	LuaState& operator=(LuaState&& other) noexcept
	{
		if (this == &other)
			return *this;
		RawState = other.RawState;
		return *this;
	}

	operator lua_State*() const;

private:
	LuaState();
	
	lua_State* RawState;
};
