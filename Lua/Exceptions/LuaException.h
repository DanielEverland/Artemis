#pragma once

#include <Exception.h>

class LuaException : public Exception
{
public:
	LuaException(int errorCode, const std::string& message);
	LuaException(int errorCode, const char* const message);

private:
	std::string GetErrorMessage(int errorCode, const std::string& customMessage) const;
	std::string GetLuaErrorMessage(int errorCode) const;
};