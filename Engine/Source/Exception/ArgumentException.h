#pragma once

#include <Exception/Exception.h>

namespace ArtemisEngine
{
	class ArgumentException : public Exception
	{
	public:
		explicit ArgumentException(const std::exception& e) : Exception(e) { }
		explicit ArgumentException(const string& message) : Exception(message) { }
		explicit ArgumentException(const char* const message) : Exception(message) { }
	};
}