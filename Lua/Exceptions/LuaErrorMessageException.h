#pragma once

#include "LuaException.h"

class LuaErrorMessageException : public LuaException
{
public:
	explicit LuaErrorMessageException(const std::exception& e) : LuaException(e) { }
	explicit LuaErrorMessageException(const string& message) : LuaException(message) { }
	explicit LuaErrorMessageException(const char* const message) : LuaException(message) { }
};
