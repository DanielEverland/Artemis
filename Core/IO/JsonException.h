#pragma once

#include "../Exceptions/Exception.h"

class JsonException : Exception
{
public:
	explicit JsonException(const std::exception& e)
		: Exception(e)
	{
	}

	explicit JsonException(const string& message)
		: Exception(message)
	{
	}

	explicit JsonException(const char* message)
		: Exception(message)
	{
	}
};
