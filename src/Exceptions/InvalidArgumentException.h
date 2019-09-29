#pragma once

#include "Exceptions.h"

class InvalidArgumentException : public Exception
{
public:
	explicit InvalidArgumentException(const std::exception& e) : Exception(e) { }
	explicit InvalidArgumentException(const string& message) : Exception(message) { }
	explicit InvalidArgumentException(const char* const message) : Exception(message) { }
};