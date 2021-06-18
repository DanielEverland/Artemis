#pragma once

#include "Exception.h"

namespace ArtemisEngine
{
	class IOException : public Exception
	{
	public:
		explicit IOException(const string& message) : Exception(message) { }
		explicit IOException(const char* const message) : Exception(message) { }
	};
}
