#pragma once

#include <stdexcept>
#include <string>

using std::string;

namespace ArtemisEngine
{
	class Exception : public std::runtime_error
	{
	public:
		explicit Exception(const std::exception& e);
		explicit Exception(const string& message);
		explicit Exception(const char* const message);

		virtual ~Exception() = default;
	};
}