#pragma once
#include "ComparisonUtility.h"

#define QuaternionExpectNear(expectedResult, actualResult) \
	TempExpectNear(expectedResult.X, actualResult.X); \
	TempExpectNear(expectedResult.Y, actualResult.Y); \
	TempExpectNear(expectedResult.Z, actualResult.Z); \
	TempExpectNear(expectedResult.W, actualResult.W);