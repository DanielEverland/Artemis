#pragma once

#include "LuaException.h"

class LuaRuntimeException : public LuaException
{
public:
	explicit LuaRuntimeException(const std::exception& e) : LuaException(e) { }
	explicit LuaRuntimeException(const string& message) : LuaException(message) { }
	explicit LuaRuntimeException(const char* const message) : LuaException(message) { }
};
