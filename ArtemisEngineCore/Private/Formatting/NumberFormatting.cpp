#include "NumberFormatting.h"

#include <iomanip>

#include "Include/Game/Math.h"

using namespace ArtemisEngine;

string NumberFormatting::Format(long value)
{
	std::stringstream stream;

	stream << value;

	return stream.str();
}
string NumberFormatting::Format(double value)
{
	std::stringstream stream;

	if (Math::IsPositiveInfinity(value))
	{
		return PositiveInfinityText;
	}
	else if (Math::IsNegativeInfinity(value))
	{
		return NegativeInfinityText;
	}
	else if (Math::IsNaN(value))
	{
		return NaNText;
	}
	else if (Math::IsFloatingPointIntegral(value))
	{
		stream << std::fixed << std::setprecision(1) << value;

		return stream.str();
	}
	else
	{
		stream << std::defaultfloat << value;

		return stream.str();
	}
}