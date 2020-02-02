#pragma once

#include "pch.h"

#include "Engine/Quaternion.h"
#include "ComparisonUtility.h"

namespace ArtemisEngine::UnitTests::Comparisons
{
	inline void ExpectEqual(Quaternion quaternion, double x, double y, double z, double w)
	{
		EXPECT_EQ(x, quaternion.X);
		EXPECT_EQ(y, quaternion.Y);
		EXPECT_EQ(z, quaternion.Z);
		EXPECT_EQ(w, quaternion.W);
	}
	inline void ExpectNear(Quaternion quaternion, double x, double y, double z, double w)
	{
		EXPECT_NEAR(x, quaternion.X, ComparisonConstants::nearComparisonPrecision);
		EXPECT_NEAR(y, quaternion.Y, ComparisonConstants::nearComparisonPrecision);
		EXPECT_NEAR(z, quaternion.Z, ComparisonConstants::nearComparisonPrecision);
		EXPECT_NEAR(w, quaternion.W, ComparisonConstants::nearComparisonPrecision);
	}
}