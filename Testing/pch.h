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

// JSON
#include <Core/IO/Json.h>

// Exceptions
#include <Core/Exceptions/ArgumentException.h>
#include <Core/Exceptions/IOException.h>

// Modding
#include <Modding/EntityType.h>

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

inline std::string GetProjectDir()
{
	std::string s = EXPAND(UNITTESTPRJ);
	s.erase(0, 1); // erase the first quote
	s.erase(s.size() - 2); // erase the last quote and the dot
	return s;
}

inline std::string GetTestFilesDir()
{
	return GetProjectDir() + "/TestFiles/";
}
