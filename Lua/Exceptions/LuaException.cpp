#include <string>
#include "LuaException.h"
#include "../Core/LuaCoreMinimal.h"

LuaException::LuaException(int errorCode, const std::string& message) : Exception(GetErrorMessage(errorCode, message))
{
	
}

LuaException::LuaException(int errorCode, const char* const message) : Exception(GetErrorMessage(errorCode, message))
{
}

std::string LuaException::GetErrorMessage(int errorCode, const std::string& customMessage) const
{
	return "Lua: " + GetLuaErrorMessage(errorCode) + ": " + customMessage;
}

std::string LuaException::GetLuaErrorMessage(int errorCode) const
{
	switch(errorCode)
	{
		case LUA_ERRSYNTAX:
			return "Syntax Error (" + std::to_string(errorCode) + ")";
		case LUA_ERRMEM:
			return "Out Of Memory (" + std::to_string(errorCode) + ")";
		case LUA_ERRERR:
			return "Message Handle Error (" + std::to_string(errorCode) + ")";
		case LUA_ERRRUN:
			return "Runtime Error (" + std::to_string(errorCode) + ")";
		case LUA_ERRFILE:
			return "File Error (" + std::to_string(errorCode) + ")";
		default:
			return "Couldn't convert " + std::to_string(errorCode) + " to Lua error code";
	}
}
