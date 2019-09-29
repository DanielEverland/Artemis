#pragma once

#include "Exceptions.h"

class NullReferenceException : public Exception
{
public:
	explicit NullReferenceException(const std::exception& e) : Exception(e) { }
	explicit NullReferenceException(const string& message) : Exception(message) { }
	explicit NullReferenceException(const char* const message) : Exception(message) { }
};