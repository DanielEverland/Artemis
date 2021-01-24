#pragma once

#include <Exception.h>

class LuaException : public Exception
{
public:
	explicit LuaException(const std::exception& e) : Exception(e) { }
	explicit LuaException(const string& message) : Exception(message) { }
	explicit LuaException(const char* const message) : Exception(message) { }

	static LuaException&& GetException(int errorCode, const std::string& message);
};