#pragma once

#include "Private/Exceptions/Exception.h"

class InvalidOperationException : Exception
{
public:
	explicit InvalidOperationException(const std::exception& e) : Exception(e) { }
	explicit InvalidOperationException(const string& message) : Exception(message) { }
	explicit InvalidOperationException(const char* const message) : Exception(message) { }
};