#pragma once

#include "Exception.h"

class OutOfRangeException : public Exception
{
public:
	explicit OutOfRangeException(const std::exception& e) : Exception(e) { }
	explicit OutOfRangeException(const string& message) : Exception(message) { }
	explicit OutOfRangeException(const char* const message) : Exception(message) { }
};