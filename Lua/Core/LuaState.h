#pragma once

#include <string>
#include <memory>

#include "LuaCoreMinimal.h"

struct LuaState
{
public:
	static std::unique_ptr<LuaState> CreateFromFile(const std::string& filePath);
	static std::unique_ptr<LuaState> CreateFromString(const std::string& rawString);

	explicit LuaState();
	
	LuaState(LuaState&& other) noexcept
		: RawState(std::move(other.RawState))
	{
	}
	
	LuaState& operator=(LuaState&& other) noexcept
	{
		if (this == &other)
			return *this;
		RawState = std::move(other.RawState);
		return *this;
	}

	operator lua_State*() const;

private:
	std::unique_ptr<lua_State, decltype(&lua_close)> RawState;
};
