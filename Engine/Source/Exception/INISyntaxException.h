#pragma once

#include "Exception.h"

namespace ArtemisEngine
{
	class INISyntaxException : public Exception
	{
	public:
		explicit INISyntaxException(const string& message) : Exception(message) { }
		explicit INISyntaxException(const char* const message) : Exception(message) { }
	};
}
