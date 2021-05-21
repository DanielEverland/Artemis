#pragma once

#include "Exception/Exception.h"

namespace ArtemisEngine
{
	class OutOfMemoryException : public Exception
	{
	public:
		explicit OutOfMemoryException(const string& message) : Exception(message) { }
		explicit OutOfMemoryException(const char* const message) : Exception(message) { }
	};
}