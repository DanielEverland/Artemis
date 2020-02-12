#pragma once

#include "ComparisonUtility.h"

#define VectorExpectNear(expectedResult, actualResult) \
	for (unsigned int i = 0; i < expectedResult.GetDimensions(); i++) \
		TempExpectNear(expectedResult[i], actualResult[i]);