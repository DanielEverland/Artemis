#pragma once

#include <Core/Exceptions/Exception.h>

class INISyntaxException : Exception
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
