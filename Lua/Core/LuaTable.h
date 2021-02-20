#pragma once

#include <string>
#include <memory>
#include <vector>
#include <utility>

#include "LuaCoreMinimal.h"
#include "LuaState.h"

using std::make_shared;
using std::vector;

using std::string;

struct LuaTable
{
public:
	explicit LuaTable(LuaState* state, LuaTable* parent, string name) : State(state), Parent(std::move(parent)), Name(std::move(name)) { }
	static LuaTable CreateRoot(const string& name, LuaState* owner);
	static LuaTable CreateChild(const string& name, LuaTable* table);
	
	LuaTable operator[](const string& childTableName);

	template<class T>
	void SetValue(T val, const string& name);

	template<class T>
	T GetValue(const string& name);

	template<class T>
	T GetValue(int index);

	[[nodiscard]] bool HasParent() const;
	
private:
	LuaState* State;
	LuaTable* Parent;
	vector<LuaTable> Children;
	string Name;

	void PushTable();
	void SaveTable();
	void GetTable();
};

template <class T>
void LuaTable::SetValue(T val, const string& name)
{
	PushTable();
	
	State->PushValue(val);
	lua_setfield(State->GetRaw(), -2, name.c_str());

	SaveTable();
}

template <class T>
T LuaTable::GetValue(const string& name)
{
	GetTable();
	
	lua_getfield(State->GetRaw(), -1, name.c_str());
	return State->GetValue<T>(-1);
}

template <class T>
T LuaTable::GetValue(int index)
{
	GetTable();

	lua_rawgeti(State->GetRaw(), -1, index + 1);
	return State->GetValue<T>(-1);
}
