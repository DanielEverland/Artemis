#pragma once

#include "Exception.h"

namespace ArtemisEngine
{
	class DirectXException : public Exception
	{
	public:
		explicit DirectXException(const string& message) : Exception(message) { }
		explicit DirectXException(const char* const message) : Exception(message) { }
	};
}
