#pragma once

#include "LuaException.h"

class LuaMemoryException : public LuaException
{
public:
	explicit LuaMemoryException(const std::exception& exception) : LuaException(exception) { }
	explicit LuaMemoryException(const string& message) : LuaException(message) { }
	explicit LuaMemoryException(const char* message) : LuaException(message) { }
};
