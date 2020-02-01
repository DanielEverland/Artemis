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
	static bool IsFloatingPointIntegral(const T& value);

	template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr >
	static bool IsPositiveInfinity(const T& value);

	template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr >
	static bool IsNegativeInfinity(const T& value);

	template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr >
	static bool IsNaN(const T& value);
};

inline const double Math::Pi = M_PI;
inline const double Math::RadToDeg = 180.0 / Math::Pi;
inline const double Math::DegToRad = Math::Pi / 180.0;
inline const double Math::Infinity = std::numeric_limits<double>::infinity();

template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
bool Math::IsFloatingPointIntegral(const T& value)
{
	return std::trunc(value) == value;
}

template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type*>
bool Math::IsPositiveInfinity(const T& value)
{
	return value == Infinity;
}

template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type*>
bool Math::IsNegativeInfinity(const T& value)
{
	return value == -Infinity;
}

template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type*>
inline bool Math::IsNaN(const T& value)
{
	return isnan(value);
}