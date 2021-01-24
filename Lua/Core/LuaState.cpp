#include <filesystem>

#include "LuaState.h"
#include "../Exceptions/LuaException.h"
#include "../Exceptions/LuaIOException.h"

std::unique_ptr<LuaState> LuaState::CreateFromFile(const std::string& filePath)
{
	if(!std::filesystem::exists(filePath))
		throw LuaIOException("Filepath \"" + filePath + "\" does not exist");
	
	auto newState = std::make_unique<LuaState>();

	const int result = luaL_dofile(*newState, filePath.c_str());
	if (result != 0)
	{
		throw LuaException::GetException(result, "Couldn't load lua file at path " + filePath);
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
		throw LuaException::GetException(result, "Couldn't create lua state from raw string");
	}
	
	return newState;
}

LuaState::LuaState() : RawState(luaL_newstate(), lua_close)
{
	luaL_openlibs(RawState.get());
}

//void LuaState::CallFunction(const std::string& funcName) const
//{
//	LoadFunction(funcName);
//	DoLuaCall(funcName, 0, 0);
//}

LuaState::operator lua_State*() const
{
	return RawState.get();
}

void LuaState::LoadFunction(const std::string& funcName) const
{
	lua_getglobal(RawState.get(), funcName.c_str());
	if(!lua_isfunction(RawState.get(), -1))
	{
		throw LuaException::GetException(LUA_ERRERR, "error loading function '" + funcName + "'");
	}		
}

void LuaState::DoLuaCall(const std::string& funcName, int argCount, int returnCount) const
{
	const int result = lua_pcall(RawState.get(), argCount, returnCount, 0);
	if (result != LUA_OK)
	{
		const auto errorMessage = "error running function '" + funcName + "': " + lua_tostring(RawState.get(), -1);
		throw LuaException::GetException(result, errorMessage);
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
