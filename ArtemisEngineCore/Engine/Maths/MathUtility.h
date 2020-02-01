#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <cmath>
#include <type_traits>
#include <limits>

class MathUtility
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

inline const double MathUtility::Pi = M_PI;
inline const double MathUtility::RadToDeg = 180.0 / MathUtility::Pi;
inline const double MathUtility::DegToRad = MathUtility::Pi / 180.0;
inline const double MathUtility::Infinity = std::numeric_limits<double>::infinity();

template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
bool MathUtility::IsFloatingPointIntegral(const T& value)
{
	return std::trunc(value) == value;
}

template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type*>
bool MathUtility::IsPositiveInfinity(const T& value)
{
	return value == Infinity;
}

template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type*>
bool MathUtility::IsNegativeInfinity(const T& value)
{
	return value == -Infinity;
}

template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type*>
inline bool MathUtility::IsNaN(const T& value)
{
	return isnan(value);
}