#include "pch.h"

#include <Core/LuaState.h>

TEST(LuaCore, FromString)
{
	lua_State* l = nullptr;
	EXPECT_EQ(l, nullptr);
	LuaState state = LuaState::CreateFromString("print \"Hello, lua\"");
}