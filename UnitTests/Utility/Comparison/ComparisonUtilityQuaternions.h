#pragma once
#include "ComparisonUtility.h"

#define QuaternionExpectNear(expectedResult, actualResult) \
	ExpectNear(expectedResult.X, actualResult.X); \
	ExpectNear(expectedResult.Y, actualResult.Y); \
	ExpectNear(expectedResult.Z, actualResult.Z); \
	ExpectNear(expectedResult.W, actualResult.W);