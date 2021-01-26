#pragma once

#include <string>
#include <memory>
#include <vector>

#include <../Lua/Exceptions/LuaException.h>

#include "LuaCoreMinimal.h"

//template<typename... Args>
//concept nonempty_pack = sizeof...(Args) > 0;

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
	
	// Calls a function with arguments but no return type
	template<typename... Inputs>
	void CallFunction(const std::string& funcName, Inputs&&... inputs);

	// Calls a function with arguments and one return type
	template<typename Output, typename... Inputs>
	disable_deduction<Output> CallFunction(const std::string& funcName, Inputs&&... inputs);

	//template< typename... Outputs, typename... Inputs > /*requires nonempty_pack<Outputs...>*/
	//std::tuple< Outputs... > CallFunctionReturn(std::string funcName, Inputs&&... inputs)
	//{
	//	lua_getglobal(RawState.get(), funcName.c_str());

	//	PushValues(inputs...);

	//	if(lua_pcall(RawState.get(), sizeof...(Inputs), sizeof...(Outputs), 0) != 0)
	//	{
	//		const auto errorMessage = "error running function '" + funcName + "': " + lua_tostring(RawState.get(), -1);
	//		throw std::exception(errorMessage.c_str());
	//	}

	//	std::tuple<Outputs...> returnValues;
	//	/*for (int i = 0; i < sizeof...(Outputs); i++)
	//	{
	//		std::get<i>(returnValues) = GetValue<typename std::tuple_element<i, std::tuple<Outputs...> >::type>(i + 1);
	//	}*/

	//	PopValues<0, std::tuple<Outputs...>, Outputs...>(returnValues);

	//	return returnValues;		
	//}

	operator lua_State*() const;

private:
	std::unique_ptr<lua_State, decltype(&lua_close)> RawState;

	lua_State* GetRaw() const;
	void LoadFunction(const std::string& funcName) const;
	void DoLuaCall(const std::string& funcName, int argCount, int returnCount) const;
	void PrintStack() const;
	
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
		{
			PrintStack();
			throw LuaRuntimeException("Failed getting integer");
		}			

		return lua_tointeger(RawState.get(), index);
	}

	template<>
	double GetValue(int index)
	{
		const int result = lua_isnumber(RawState.get(), index);
		if (result != LUA_OK)
			throw LuaRuntimeException("Failed getting double");

		return lua_tonumber(RawState.get(), index);
	}

	template<>
	std::string GetValue(int index)
	{
		const int result = lua_isstring(RawState.get(), index);
		if (result != LUA_OK)
			throw LuaRuntimeException("Failed getting string");

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

	template<unsigned int I, typename Tuple, typename Output, typename ...Outputs>
	void PopValues(Tuple returnValues)
	{
		std::get<I>(returnValues) = GetValue<Output>(I);
		return PopValues<I + 1, Tuple, Outputs...>(returnValues);
	}

	template<unsigned int I, typename Tuple, typename Output>
	void PopValues(Tuple returnValues)
	{
		std::get<I>(returnValues) = GetValue<Output>(I);
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
	
	DoLuaCall(funcName, sizeof...(Inputs), 1);
	return GetValue<Output>(LUA_STACK_TOP);
}
