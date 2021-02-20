#include "LuaTable.h"

LuaTable LuaTable::CreateChild(const string& name, LuaTable* table)
{
	return LuaTable(table->State, table, name);
}

LuaTable LuaTable::operator[](const string& childTableName)
{
	Children.push_back(CreateChild(childTableName, this));
	return Children.back();
}

bool LuaTable::HasParent() const
{
	return Parent != nullptr;
}

void LuaTable::PushTable()
{
	lua_newtable(State->GetRaw());

	if(HasParent())
		Parent->PushTable();
}

void LuaTable::SaveTable()
{
	if (HasParent())
	{
		lua_setfield(State->GetRaw(), -2, Name.c_str());
		Parent->SaveTable();
	}
	else
	{
		lua_setglobal(State->GetRaw(), Name.c_str());
	}
}

void LuaTable::GetTable()
{
	if(HasParent())
	{
		Parent->GetTable();
		lua_getfield(State->GetRaw(), -1, Name.c_str());
	}
	else
	{
		lua_getglobal(State->GetRaw(), Name.c_str());
	}
}

LuaTable LuaTable::CreateRoot(const string& name, LuaState* owner)
{
	return LuaTable(owner, nullptr, name);
}
