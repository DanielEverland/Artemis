#include "pch.h"

#include <Core/LuaState.h>
#include <Lua/Exceptions/LuaIOException.h>
#include <Lua/Exceptions/LuaSyntaxException.h>

TEST(LuaCore, TwoArgumentsNoReturnFromFile)
{
	int a = 42;
	int b = 69;
	LuaState::CreateFromFile(GetTestFilesDir() + "TwoArgumentsNoReturnFromFile.lua")->CallFunction("func", a, b);
}

TEST(LuaCore, OneArgumentNoReturnFromFile)
{
	int a = 42;
	LuaState::CreateFromFile(GetTestFilesDir() + "OneArgumentNoReturnFromFile.lua")->CallFunction("func", a);
}

TEST(LuaCore, TwoArgumentsNoReturnFromString)
{
	int a = 42;
	int b = 69;
	LuaState::CreateFromString("function func(a, b) print(a + b) end")->CallFunction("func", a, b);
}

TEST(LuaCore, OneArgumentNoReturnFromString)
{
	int a = 42;
	LuaState::CreateFromString("function func(a) print(a) end")->CallFunction("func", a);
}

TEST(LuaCore, NoArgumentsNoReturnFromString)
{
	LuaState::CreateFromString("function func() print(\"test\") end")->CallFunction("func");
}

TEST(LuaCore, NoArgumentsNoReturnFromFile)
{
	LuaState::CreateFromFile(GetTestFilesDir() + "NoArgumentsNoReturnFromFile.lua")->CallFunction("func");
}

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

TEST(LuaCore, MissingFunction)
{
	EXPECT_THROW(LuaState::CreateFromString("function func() print(\"test\") end")->CallFunction("funcc"), LuaSyntaxException);
}

TEST(LuaCore, FromStringError)
{
	EXPECT_THROW(LuaState::CreateFromString("this will cause an error"), LuaSyntaxException);
}

TEST(LuaCore, FromFileError)
{
	EXPECT_THROW(LuaState::CreateFromFile(GetTestFilesDir() + "FromFileError.lua"), LuaSyntaxException);
}

TEST(LuaCore, ReturnTuple)
{
	const std::string rawString = "function func(a, b) return a, b end";
	auto state = LuaState::CreateFromString(rawString);

	int firstParam = 420;
	float secondParam = 69.66f;
	
	auto returnValue = state->CallFunction<int, float>("func", firstParam, secondParam);
	
	EXPECT_EQ(std::get<0>(returnValue), firstParam);
	EXPECT_EQ(std::get<1>(returnValue), secondParam);
}

TEST(LuaCore, CreateTable)
{
	LuaState state;
	EXPECT_NO_THROW(state.CreateGlobalTable("table"));
}

TEST(LuaCore, PushTableString)
{
	const string tableName = "table";
	LuaState state;
	state.CreateGlobalTable(tableName);
	EXPECT_NO_THROW(state.PushTableString(tableName, "stringKey", "stringValue"));	
}

TEST(LuaCore, ReadTableStringFromRawLua)
{
	const string tableName = "table";
	const string keyName = "stringKey";
	const string valueName = "stringValue";
	const string rawLua = "function func() return " + tableName + "[\"" + keyName + "\"] end";
	
	auto state = LuaState::CreateFromString(rawLua);
	state->CreateGlobalTable(tableName);
	state->PushTableString(tableName, keyName, valueName);
	const string actualOutput = state->CallFunction<string>("func");
	EXPECT_EQ(actualOutput, valueName);
}

TEST(LuaCore, PushTableStringUnchangedStackSize)
{
	const string tableName = "table";
	LuaState state;

	const int preStackSize = state.GetStackSize();
	state.CreateGlobalTable(tableName);
	state.PushTableString(tableName, "stringKey", "stringValue");
	EXPECT_EQ(state.GetStackSize(), preStackSize);
}

TEST(LuaCore, RunFunctionImmediately)
{
	const string rawLua = "function func() print(\"test\") end func()";
	EXPECT_NO_THROW(auto state = LuaState::CreateFromString(rawLua));	
}

TEST(LuaCore, HasFunctionProper)
{
	const string rawLua = "function func() end";
	EXPECT_TRUE(LuaState::CreateFromString(rawLua)->HasFunction("func"));
}

TEST(LuaCore, HasFunctionNone)
{
	const string rawLua = "function notFuncName() end";
	EXPECT_FALSE(LuaState::CreateFromString(rawLua)->HasFunction("func"));
}

TEST(LuaCore, HasFunctionVariableName)
{
	const string rawLua = "func = 2";
	EXPECT_FALSE(LuaState::CreateFromString(rawLua)->HasFunction("func"));
}

TEST(LuaCore, HasFunctionStackSizeRetentionTrue)
{
	const string rawLua = "function func() end";
	auto state = LuaState::CreateFromString(rawLua);
	const int preStackSize = state->GetStackSize();
	const bool hasFunction = state->HasFunction("func");
	EXPECT_EQ(state->GetStackSize(), preStackSize);
}

TEST(LuaCore, HasFunctionStackSizeRetentionFalse)
{
	const string rawLua = "func = 2";
	auto state = LuaState::CreateFromString(rawLua);
	const int preStackSize = state->GetStackSize();
	const bool hasFunction = state->HasFunction("func");
	EXPECT_EQ(state->GetStackSize(), preStackSize);
}