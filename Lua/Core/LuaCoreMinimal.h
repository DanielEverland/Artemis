#pragma once

#include <Lua/Src/lua.h>
#include <Lua/Src/lualib.h>
#include <Lua/Src/lauxlib.h>


#include "LuaMagicNumbers.h"

#include <Lua/Exceptions/LuaException.h>
#include <Lua/Exceptions/LuaIOException.h>
#include <Lua/Exceptions/LuaSyntaxException.h>
#include <Lua/Exceptions/LuaMemoryException.h>
#include <Lua/Exceptions/LuaRuntimeException.h>
#include <Lua/Exceptions/LuaErrorMessageException.h>

#define LUA_STACK_TOP -1
#define LUA_STACK_BOTTOM 1

#define THROW_IF_ERROR(result, message) if(result != 0) throw LuaException::GetException(result,  message);

inline std::string TypeToString(int type)
{
	switch (type)
	{
	case LUA_TNIL: return "Lua_Nil";
	case LUA_TBOOLEAN: return "Lua_Boolean";
	case LUA_TLIGHTUSERDATA: return "Lua_LightUserData";
	case LUA_TNUMBER: return "Lua_Number";
	case LUA_TSTRING: return "Lua_String";
	case LUA_TTABLE: return "Lua_Table";
	case LUA_TFUNCTION: return "Lua_Function";
	case LUA_TUSERDATA: return "Lua_UserData";
	case LUA_TTHREAD: return "Lua_Thread";
	default: return "Lua_UnknownType (" + std::to_string(type) + ")";
	}
}