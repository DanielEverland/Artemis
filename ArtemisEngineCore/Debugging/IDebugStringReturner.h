#pragma once

#include <string>

namespace ArtemisEngine::Debugging
{
	class IDebugStringReturner
	{
	public:
		virtual std::string ToString() const = 0;
	};
}