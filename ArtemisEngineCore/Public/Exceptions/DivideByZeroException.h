#pragma once

#include "Private/Exceptions/Exception.h"

class DivideByZeroException : public Exception
{
public:
	DivideByZeroException() : Exception("Attempted to divide by zero") { }

	explicit DivideByZeroException(const std::exception& e) : Exception(e) { }
	explicit DivideByZeroException(const string& message) : Exception(message) { }
	explicit DivideByZeroException(const char* const message) : Exception(message) { }
};