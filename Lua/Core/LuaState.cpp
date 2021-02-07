﻿#include <filesystem>

#include "LuaState.h"
#include "../Exceptions/LuaException.h"
#include "../Exceptions/LuaIOException.h"
#include "../Exceptions/LuaSyntaxException.h"

std::unique_ptr<LuaState> LuaState::CreateFromFile(const std::string& filePath)
{
	if(!std::filesystem::exists(filePath))
		throw LuaIOException("Filepath \"" + filePath + "\" does not exist");
	
	auto newState = std::make_unique<LuaState>();

	const int result = luaL_dofile(*newState, filePath.c_str());
	if (result != 0)
	{
		throw LuaSyntaxException("Couldn't load lua file at path " + filePath);
	}
	newState->PrintStack();
	
	return newState;
}

std::unique_ptr<LuaState> LuaState::CreateFromString(const std::string& rawString)
{
	auto newState = std::make_unique<LuaState>();

	const int result = luaL_dostring(*newState, rawString.c_str());
	if(result != 0)
	{
		throw LuaSyntaxException("Couldn't create lua state from raw string");
	}
	
	return newState;
}

LuaState::LuaState() : RawState(luaL_newstate(), lua_close)
{
	luaL_openlibs(RawState.get());
}

int LuaState::GetStackSize() const
{
	return lua_gettop(GetRaw());
}

bool LuaState::HasFunction(const string& functionName) const
{
	const int loadedType = lua_getglobal(RawState.get(), functionName.c_str()) != LUA_TNIL;
	if(loadedType == LUA_TNIL)
		return false;

	const bool isFunction = lua_isfunction(GetRaw(), -1);
	lua_remove(GetRaw(), -1);
	
	return isFunction;
}

void LuaState::CreateGlobalTable(const string& tableName) const
{
	lua_newtable(GetRaw(), tableName.c_str());
	lua_setglobal(GetRaw(), tableName.c_str());
}

void LuaState::PushTableString(const string& tableName, const string& key, const string& value) const
{
	lua_getglobal(GetRaw(), tableName.c_str());
	lua_pushstring(GetRaw(), key.c_str());
	lua_pushstring(GetRaw(), value.c_str());
	lua_settable(GetRaw(), -3);
	// Pop the table from the stack
	lua_remove(GetRaw(), -1);
}

LuaState::operator lua_State*() const
{
	return GetRaw();
}

lua_State* LuaState::GetRaw() const
{
	return RawState.get();
}

void LuaState::LoadFunction(const std::string& funcName) const
{
	const int loadedType = lua_getglobal(RawState.get(), funcName.c_str());
	if(loadedType == LUA_TNIL)
	{
		throw LuaSyntaxException("Error loading function '" + funcName + "'. Return Code = " + TypeToString(loadedType));
	}		
}

void LuaState::DoLuaCall(const std::string& funcName, int argCount, int returnCount) const
{
	const int result = lua_pcall(RawState.get(), argCount, returnCount, 0);	
	if (result != LUA_OK)
	{
		std::string luaErrorMessage = "N/A";
		if(lua_isstring(GetRaw(), -1))
		{
			luaErrorMessage = lua_tostring(RawState.get(), -1);
		}			

		const auto completeErrorMessage = "Error calling function '" + funcName + "'. Lua Error Message: " + lua_tostring(RawState.get(), -1);
		
		switch (result)
		{
			case LUA_ERRRUN: throw LuaRuntimeException(completeErrorMessage);
			case LUA_ERRERR: throw LuaErrorMessageException(completeErrorMessage);
			case LUA_ERRMEM: throw LuaMemoryException(completeErrorMessage);
			default: throw LuaException("Unknown error code. " + completeErrorMessage);
		}
	}
}

void LuaState::PrintStack() const
{
    int i;
    int top = lua_gettop(RawState.get());
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(RawState.get(), i);
        switch (t) {

        case LUA_TSTRING:  /* strings */
		{
			string val(lua_tostring(RawState.get(), i));
            printf("`%s'", val.c_str());
            break;
        }

        case LUA_TBOOLEAN:  /* booleans */
            printf(lua_toboolean(RawState.get(), i) ? "true" : "false");
            break;

        case LUA_TNUMBER:  /* numbers */
	    {
			lua_Number nmbr = lua_tonumber(RawState.get(), i);
			int integer = nmbr;
			double floatpoint = nmbr;
			printf("%g", lua_tonumber(RawState.get(), i));
			break;
	    }
			

        default:  /* other values */
            printf("%s", lua_typename(RawState.get(), t));
            break;

        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
    printf("\n");  /* end the listing */
}

string LuaState::GetStackType(int index) const
{
	int type = lua_type(GetRaw(), index);
	switch(type)
	{
		case LUA_TNONE:
			return "None";
		case LUA_TNIL:
			return "Nil";
		case LUA_TBOOLEAN:
			return "Boolean";
		case LUA_TLIGHTUSERDATA:
			return "LightUserData";
		case LUA_TNUMBER:
			return "Number";
		case LUA_TSTRING:
			return "String";
		case LUA_TTABLE:
			return "Table";
		case LUA_TFUNCTION:
			return "Function";
		case LUA_TUSERDATA:
			return "UserData";
		case LUA_TTHREAD:
			return "Thread";
		default:
			return "Unknown";
	}
}

LuaRuntimeException LuaState::GetGettingValueException(const string& expectedValueType, int index) const
{
	return LuaRuntimeException("Failed getting " + expectedValueType + ". Actual type: " + GetStackType(index));
}
