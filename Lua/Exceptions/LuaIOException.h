#pragma once

#include "LuaException.h"

class LuaIOException : public LuaException
{
public:
	explicit LuaIOException(const std::exception& e) : LuaException(e) { }
	explicit LuaIOException(const string& message) : LuaException(message) { }
	explicit LuaIOException(const char* const message) : LuaException(message) { }
};
