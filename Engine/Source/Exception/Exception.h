#pragma once

#include <stdexcept>
#include <string>

using std::string;

namespace ArtemisEngine
{
	class Exception : public std::runtime_error
	{
	public:
		explicit Exception(const string& message) : runtime_error(message) { }
		explicit Exception(const char* const message) : runtime_error(message) { }

		virtual ~Exception() = default;
	};
}