#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <cmath>
#include <type_traits>
#include <limits>

class Math
{
public:
	static const double Pi;
	static const double RadToDeg;
	static const double DegToRad;
	static const double Infinity;

	template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr >
	static bool IsFloatingPointIntegral(T value)
	{
		return std::trunc(value) == value;
	}

	template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr >
	static bool IsPositiveInfinity(T value)
	{
		return value == Infinity;
	}

	template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr >
	static bool IsNegativeInfinity(T value)
	{
		return value == -Infinity;
	}

	template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr >
	static bool IsNaN(T value)
	{
		return isnan(value);
	}
};