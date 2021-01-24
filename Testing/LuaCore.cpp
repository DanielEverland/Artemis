#include "pch.h"

#include <Core/LuaState.h>
#include <Lua/Exceptions/LuaIOException.h>
#include <Lua/Exceptions/LuaSyntaxException.h>

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

TEST(LuaCore, OneArgumentOneReturnFromString)
{
	const int value = 42;
	auto state = LuaState::CreateFromString("function func(a) return a end");
	int returnValue = state->CallFunction<int>("func", value);
	EXPECT_EQ(returnValue, value);
}

TEST(LuaCore, TwoArgumentsOneReturnFromString)
{
	const int a = 42;
	const int b = 69;
	const int expectedReturn = a + b;
	auto state = LuaState::CreateFromString("function func(a, b) return a + b end");
	int returnValue = state->CallFunction<int>("func", a, b);
	EXPECT_EQ(returnValue, expectedReturn);
}

TEST(LuaCore, OneArgumentOneReturnFromFile)
{
	const int value = 42;
	auto state = LuaState::CreateFromFile(GetTestFilesDir() + "OneArgumentOneReturnFromFile.lua");
	int returnValue = state->CallFunction<int>("func", value);
	EXPECT_EQ(returnValue, value);
}

TEST(LuaCore, TwoArgumentsOneReturnFromFile)
{
	const int a = 42;
	const int b = 69;
	const int expectedReturn = a + b;
	auto state = LuaState::CreateFromFile(GetTestFilesDir() + "TwoArgumentsOneReturnFromFile.lua");
	int returnValue = state->CallFunction<int>("func", a, b);
	EXPECT_EQ(returnValue, expectedReturn);
}

TEST(LuaCore, InvalidFilePath)
{
	EXPECT_THROW(LuaState::CreateFromFile("invalid path"), LuaIOException);
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