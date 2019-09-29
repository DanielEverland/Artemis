#pragma once

#include "Exceptions.h"

class DirectXException : public Exception
{
public:
	explicit DirectXException(const std::exception& e) : Exception(e) { }
	explicit DirectXException(const string& message) : Exception(message) { }
	explicit DirectXException(const char* const message) : Exception(message) { }
};