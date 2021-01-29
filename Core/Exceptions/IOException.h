#pragma once

#include "Exception.h"

class IOException : Exception
{
public:
	explicit IOException(const std::exception& e)
		: Exception(e)
	{
	}

	explicit IOException(const string& message)
		: Exception(message)
	{
	}

	explicit IOException(const char* message)
		: Exception(message)
	{
	}
};
