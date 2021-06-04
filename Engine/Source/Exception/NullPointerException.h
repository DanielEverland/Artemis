#pragma once

#include "Exception.h"

namespace ArtemisEngine
{
	class NullPointerException : public Exception
	{
	public:
		explicit NullPointerException(const string& message) : Exception(message) { }
		explicit NullPointerException(const char* const message) : Exception(message) { }
	};
}