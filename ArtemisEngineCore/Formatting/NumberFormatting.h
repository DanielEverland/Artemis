#pragma once

#include <string>
#include <sstream>
#include <type_traits>

using std::string;

namespace ArtemisEngine
{
	class NumberFormatting
	{
	public:
		template<class T>
		static string FormatGeneric(T value)
		{
			if constexpr (std::is_floating_point<T>::value)
			{
				return Format(double(value));
			}
			else if constexpr (std::is_integral<T>::value)
			{
				return Format(long(value));
			}
			else
			{
				static_assert("Cannot format type");
			}
		}
		static string Format(double value);
		static string Format(long value);

	private:
		inline static const string PositiveInfinityText = "PositiveInfinity";
		inline static const string NegativeInfinityText = "NegativeInfinity";
		inline static const string NaNText = "NaN";
	};
}