#pragma once

#include "Exception.h"

class InvalidOperationException : public Exception
{
public:
	explicit InvalidOperationException(const std::exception& e)
		: Exception(e)
	{
	}

	explicit InvalidOperationException(const string& message)
		: Exception(message)
	{
	}

	explicit InvalidOperationException(const char* message)
		: Exception(message)
	{
	}
};
