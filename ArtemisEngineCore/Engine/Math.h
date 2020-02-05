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

	template<class T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr >
	static T Absolute(T value)
	{
		return std::abs(value);
	}

	// Returns the value of x with the sign of y
	template<class T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr >
	static T CopySign(T x, T y)
	{
		return std::copysign(x, y);
	}

	static double ArcTan2(double x, double y)
	{
		return std::atan2(x, y);
	}

	template<class T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr >
	static T ArcCos(T value)
	{
		return std::acos(value);
	}

	template<class T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr >
	static T Cos(T value)
	{
		return std::cos(value);
	}

	template<class T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr >
	static T ArcSin(T value)
	{
		return std::asin(value);
	}

	template<class T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr >
	static T Sin(T value)
	{
		return std::sin(value);
	}

	template<class T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr >
	static T ArcTan(T value)
	{
		return std::atan(value);
	}

	template<class T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr >
	static T Tan(T value)
	{
		return std::tan(value);
	}

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