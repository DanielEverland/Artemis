#pragma once

#include <string>

namespace ArtemisEngine
{
	class IDebugStringReturner
	{
	public:
		virtual std::string ToString() const = 0;
	};
}