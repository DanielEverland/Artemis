#pragma once

#include "Exception.h"

class ArgumentException : public Exception
{
public:
	explicit ArgumentException(const std::exception& e)
		: Exception(e)
	{
	}

	explicit ArgumentException(const string& message)
		: Exception(message)
	{
	}

	explicit ArgumentException(const char* message)
		: Exception(message)
	{
	}
};
