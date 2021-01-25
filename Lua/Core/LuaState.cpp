#include <filesystem>

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

void LuaState::CallFunction(const std::string& funcName) const
{
	LoadFunction(funcName);
	DoLuaCall(funcName, 0, 0);
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
            printf("`%s'", lua_tostring(RawState.get(), i));
            break;

        case LUA_TBOOLEAN:  /* booleans */
            printf(lua_toboolean(RawState.get(), i) ? "true" : "false");
            break;

        case LUA_TNUMBER:  /* numbers */
            printf("%g", lua_tonumber(RawState.get(), i));
            break;

        default:  /* other values */
            printf("%s", lua_typename(RawState.get(), t));
            break;

        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
    printf("\n");  /* end the listing */
}
