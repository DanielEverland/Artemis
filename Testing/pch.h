//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"

#define LUA_USE_APICHECK

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

//#include <Core/LuaState.h>
