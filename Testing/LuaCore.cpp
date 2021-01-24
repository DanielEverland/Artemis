#include "pch.h"

#include <Core/LuaState.h>

//TEST(LuaCore, FunctionArguments)
//{
//	const std::string rawString = "function func(a, b) print(\"test\") end";
//	auto state = LuaState::CreateFromString(rawString);
//
//	int firstParam = 1;
//	float secondParam = 2.5f;
//
//	state->CallFunction("func", firstParam, secondParam);
//}

//TEST(LuaCore, RawLua)
//{
//	lua_State* L = luaL_newstate();
//	luaL_openlibs(L);
//
//	int code = luaL_dofile(L, "C:/Users/Daniel/Desktop/test.lua");
//	int funcReturnCode = lua_getglobal(L, "func");
//	lua_pcall(L, 0, 1, 0);
//	int returnValCode = lua_isnumber(L, -1);
//	int returnValCode2 = lua_isinteger(L, -1);
//	auto value = lua_tonumber(L, -1);
//	auto errMsg = lua_tostring(L, -1);
//
//	EXPECT_EQ(value, 69);
//}

TEST(LuaCore, NoArgumentsOneReturnFromFile)
{
	const int value = 69;
	auto state = LuaState::CreateFromFile(GetTestFilesDir() + "NoArgumentsOneReturnFromFile.lua");
	int returnValue = state->CallFunction<int>("func");
	EXPECT_EQ(returnValue, value);
}

TEST(LuaCore, NoArgumentsOneReturnFromString)
{
	const int value = 42;
	auto state = LuaState::CreateFromString("function func() return " + std::to_string(value) + " end");
	int returnValue = state->CallFunction<int>("func");
	EXPECT_EQ(returnValue, value);
}

//TEST(LuaCore, ReturnTuple)
//{
//	const std::string rawString = "function func(a, b) return a, b end";
//	auto state = LuaState::CreateFromString(rawString);
//
//	int firstParam = 1;
//	float secondParam = 2.5f;
//	
//	auto returnValue = state->CallFunctionReturn<int, float>("func", firstParam, secondParam);
//	
//	EXPECT_EQ(std::get<0>(returnValue), firstParam);
//	EXPECT_EQ(std::get<1>(returnValue), secondParam);
//}