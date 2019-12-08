#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

class MathUtility
{
public:
	static const double Pi;
	static const double RadToDeg;
	static const double DegToRad;
};

const double MathUtility::Pi = M_PI;
const double MathUtility::RadToDeg = 180.0 / MathUtility::Pi;
const double MathUtility::DegToRad = MathUtility::Pi / 180.0;