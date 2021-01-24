#include <string>
#include "LuaException.h"
#include "../Core/LuaCoreMinimal.h"
#include "LuaIOException.h"
#include "LuaRuntimeException.h"
#include "LuaErrorMessageException.h"
#include "LuaMemoryException.h"
#include "LuaSyntaxException.h"

LuaException&& LuaException::GetException(int errorCode, const std::string& message)
{
	switch (errorCode)
	{
	case LUA_ERRSYNTAX:
		return std::move(LuaSyntaxException(message));
	case LUA_ERRMEM:
		return std::move(LuaMemoryException(message));
	case LUA_ERRERR:
		return std::move(LuaErrorMessageException(message));
	case LUA_ERRRUN:
		return std::move(LuaRuntimeException(message));
	case LUA_ERRFILE:
		return std::move(LuaIOException(message));
	default:
		return std::move(LuaException(message));
	}
}
