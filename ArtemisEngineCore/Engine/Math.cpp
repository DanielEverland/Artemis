#include "Math.h"

const double Math::Pi = M_PI;
const double Math::Infinity = std::numeric_limits<double>::infinity();
const double Math::NaN = nan("");

double Math::NormalizeAngle(double angle)
{	
	angle = Math::Remainder(angle, 360);

	// force it to be the positive remainder, so that 0 <= angle < 360  
	angle = Math::Remainder(angle + 360, 360);

	// force into the minimum absolute value residue class, so that -180 < angle <= 180
	if (angle > 180)
		angle -= 360;

	return angle;

}

double Math::Remainder(double numerator, double denominator)
{
	return std::fmod(numerator, denominator);
}

double Math::RadiansToDegrees(double value)
{
	return value * 180.0 / Math::Pi;
}

double Math::DegreesToRadians(double value)
{
	return value * Math::Pi / 180.0;
}

double Math::Power(double value, double power)
{
	return std::pow(value, power);
}

double Math::SquareRoot(double value)
{
	if (value < 0)
		return Math::NaN;

	return std::sqrt(value);
}

double Math::ArcTangent2(double x, double y)
{
	return std::atan2(x, y);
}

double Math::Cosine(double angle)
{
	return std::cos(angle);
}

double Math::ArcCosine(double value)
{
	return std::acos(value);
}

double Math::Sine(double angle)
{
	return std::sin(angle);
}

double Math::ArcSine(double value)
{
	return std::asin(value);
}

double Math::Tangent(double angle)
{
	return std::tan(angle);
}

double Math::ArcTangent(double value)
{
	return std::atan(value);
}