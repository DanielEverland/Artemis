#pragma once

#include <Exception.h>

class ModException : public Exception
{
public:
	explicit ModException(const std::exception& e)
		: Exception(e)
	{
	}

	explicit ModException(const string& message)
		: Exception(message)
	{
	}

	explicit ModException(const char* message)
		: Exception(message)
	{
	}
};
