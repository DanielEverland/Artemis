#pragma once

#include "LuaException.h"

class LuaSyntaxException : public LuaException
{
public:
	explicit LuaSyntaxException(const std::exception& e) : LuaException(e) { }
	explicit LuaSyntaxException(const string& message) : LuaException(message) { }
	explicit LuaSyntaxException(const char* const message) : LuaException(message) { }
};
