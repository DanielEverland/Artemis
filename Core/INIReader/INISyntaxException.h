#pragma once

#include <../Exceptions/Exception.h>

class INISyntaxException : public Exception
{
public:
	explicit INISyntaxException(const std::exception& e)
		: Exception(e)
	{
	}

	explicit INISyntaxException(const string& message)
		: Exception(message)
	{
	}

	explicit INISyntaxException(const char* message)
		: Exception(message)
	{
	}
};
