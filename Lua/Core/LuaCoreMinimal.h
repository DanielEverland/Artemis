#pragma once

// Lua
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <../Lua/Exceptions/LuaException.h>

#define LUA_STACK_TOP -1
#define LUA_STACK_BOTTOM 1

#define THROW_IF_ERROR(result, message) if(result != 0) throw LuaException::GetException(result,  message);