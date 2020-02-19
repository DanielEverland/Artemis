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
	static const double Infinity;
	static const double NaN;

	// Returns an angle in the range (-180;180]
	static double NormalizeAngle(double value);

	// "Left over" after dividing the numerator with the denominator (numerator/denominator)
	// Will return same sign as numerator
	static double Remainder(double numerator, double denominator);

	// Converts radians into degrees
	static double RadiansToDegrees(double value);

	// Converts degrees into radians
	static double DegreesToRadians(double value);

	// Squares value.
	// Useful in long equations where writing it out manually is too messy.
	template<class T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr >
	static T Square(T value)
	{
		return value * value;
	}
	
	// Returns value raised to power.
	static double Power(double value, double power);

	// Returns the square root of value.
	static double SquareRoot(double value);

	// Returns positive value
	template<class T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr >
	static T Absolute(T value)
	{
		return std::abs(value);
	}

	// Copies the sign to value
	template<class TValue, class TSign,
		typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr,
		typename std::enable_if<std::is_arithmetic<TSign>::value>::type * = nullptr>
	static TValue CopySign(TValue value, TSign sign)
	{
		return std::copysign(value, sign);
	}

	// Returns the angle in radians between x-axis and the ray of point (x, y)
	static double ArcTangent2(double x, double y);
	
	/// <summary>Computes the cosine of angle given in radians</summary>
	/// <param name="angle">Given in radians</param>
	static double Cosine(double angle);

	// Computes the angle given the value of cosine
	static double ArcCosine(double value);

	/// <summary>Computes the sine of angle given in radians</summary>
	/// <param name="angle">Given in radians</param>
	static double Sine(double angle);
	 
	// Computes the angle given the value of sine
	static double ArcSine(double value);

	/// <summary>Computes the tangent of angle given in radians</summary>
	/// <param name="angle">Given in radians</param>
	static double Tangent(double angle);

	// Computes the angle given the value of tangent
	static double ArcTangent(double value);
	
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