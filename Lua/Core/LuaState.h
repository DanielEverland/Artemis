#pragma once

#include <string>
#include <memory>

#include <Lua/Exceptions/LuaException.h>

#include "LuaCoreMinimal.h"

template<typename T>
struct type_identity
{
	using type = T;
};

template<class T>
using disable_deduction = typename type_identity<T>::type;

struct LuaState
{
public:
	static std::unique_ptr<LuaState> CreateFromFile(const std::string& filePath);
	static std::unique_ptr<LuaState> CreateFromString(const std::string& rawString);

	explicit LuaState();

	int GetStackSize() const;
	bool HasFunction(const string& functionName) const;
	
	// Calls a function with arguments but no return type
	template<typename... Inputs>
	void CallFunction(const std::string& funcName, Inputs&&... inputs);

	// Creates a global table to the state
	void CreateGlobalTable(const string& tableName) const;

	// Pushes a string to the global table
	void PushTableString(const string& tableName, const string& key, const string& value) const;

	// Calls a function with arguments and one return type
	template<typename Output, typename... Inputs>
	disable_deduction<Output> CallFunction(const std::string& funcName, Inputs&&... inputs);

	template<typename... Outputs, typename... Inputs, std::size_t i = sizeof...(Outputs), std::enable_if_t<(i > 1), int> = 0>
	std::tuple<Outputs...> CallFunction(std::string funcName, Inputs&&... inputs);

	operator lua_State*() const;

private:
	std::unique_ptr<lua_State, decltype(&lua_close)> RawState;

	static int CFunc_NewEntity(lua_State* luaState);

	void ExposeFunction(const string& functionName, lua_CFunction func);
	lua_State* GetRaw() const;
	void LoadFunction(const std::string& funcName) const;
	void DoLuaCall(const std::string& funcName, int argCount, int returnCount) const;
	void PrintStack() const;
	string GetStackType(int index) const;
	LuaRuntimeException GetGettingValueException(const string& expectedValueType, int index) const;
	
	template<typename T>
	void PushValue(T val)
	{
		static_assert(true, "PushValue: Could not find specialization");
	}

	template<>
	void PushValue(int val)
	{
		lua_pushinteger(RawState.get(), val);
	}

	template<>
	void PushValue(double val)
	{
		lua_pushnumber(RawState.get(), val);
	}

	template<>
	void PushValue(float val)
	{
		lua_pushnumber(RawState.get(), val);
	}

	template<>
	void PushValue(const std::string& val)
	{
		lua_pushstring(RawState.get(), val.c_str());
	}

	template<typename T>
	T GetValue(int index)
	{
		static_assert(true, "GetValue: Could not find specialization");
	}

	template<>
	int GetValue(int index)
	{
		const bool result = lua_isinteger(RawState.get(), index);
		if (!result)
			throw GetGettingValueException("int", index);

		return static_cast<int>(lua_tointeger(RawState.get(), index));
	}

	template<>
	double GetValue(int index)
	{
		const bool result = lua_isnumber(RawState.get(), index);
		if (!result)
			throw GetGettingValueException("double", index);

		return static_cast<double>(lua_tonumber(RawState.get(), index));
	}

	template<>
	float GetValue(int index)
	{
		const bool result = lua_isnumber(RawState.get(), index);
		if (!result)
			throw GetGettingValueException("float", index);

		return static_cast<float>(lua_tonumber(RawState.get(), index));
	}

	template<>
	std::string GetValue(int index)
	{
		const bool result = lua_isstring(RawState.get(), index);
		if (!result)
			throw GetGettingValueException("string", index);

		return lua_tostring(RawState.get(), index);
	}
	
	template<typename Input, typename ...Inputs>
	void PushValues(Input&& input, Inputs&&... inputs)
	{
		PushValue(input);
		return PushValues(inputs...);
	}

	template<typename Input>
	void PushValues(Input&& input)
	{
		PushValue(input);
	}

	template<unsigned int I, typename Tuple, typename Output, typename ...Outputs, std::size_t i = sizeof...(Outputs), std::enable_if_t<(i > 0), int> = 0>
	void PopValues(Tuple& returnValues)
	{
		Output val = GetValue<Output>((sizeof...(Outputs) + 1 - I) * -1);
		std::get<I>(returnValues) = val;
		return PopValues<I + 1, Tuple, Outputs...>(returnValues);
	}

	template<unsigned int I, typename Tuple, typename Output>
	void PopValues(Tuple& returnValues)
	{
		Output val = GetValue<Output>(-1);
		std::get<I>(returnValues) = val;
	}
};

template <typename ... Inputs>
void LuaState::CallFunction(const std::string& funcName, Inputs&&... inputs)
{
	LoadFunction(funcName);
	
	if constexpr (sizeof...(Inputs) > 0)
	{
		PushValues(inputs...);
	}
	
	DoLuaCall(funcName, sizeof...(Inputs), 0);
}

template <typename Output, typename ... Inputs>
disable_deduction<Output> LuaState::CallFunction(const std::string& funcName, Inputs&&... inputs)
{
	LoadFunction(funcName);

	if constexpr(sizeof...(Inputs) > 0)
	{
		PushValues(inputs...);
	}

	PrintStack();
	DoLuaCall(funcName, sizeof...(Inputs), 1);
	return GetValue<Output>(LUA_STACK_TOP);
}

template <typename ... Outputs, typename ... Inputs, std::size_t i, std::enable_if_t<(i > 1), int>>
std::tuple<Outputs...> LuaState::CallFunction(std::string funcName, Inputs&&... inputs)
{
	LoadFunction(funcName);

	if constexpr (sizeof...(Inputs) > 0)
	{
		PushValues(inputs...);
	}

	DoLuaCall(funcName, sizeof...(Inputs), sizeof...(Outputs));

	std::tuple<Outputs...> returnValues;
	PopValues<0, std::tuple<Outputs...>, Outputs...>(returnValues);

	return returnValues;
}