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
		EXPECT_NEAR(x, quaternion.X, NearComparisonPrecision);
		EXPECT_NEAR(y, quaternion.Y, NearComparisonPrecision);
		EXPECT_NEAR(z, quaternion.Z, NearComparisonPrecision);
		EXPECT_NEAR(w, quaternion.W, NearComparisonPrecision);
	}
	inline void ExpectEqual(Quaternion a, Quaternion b)
	{
		EXPECT_EQ(a.X, b.X);
		EXPECT_EQ(a.Y, b.Y);
		EXPECT_EQ(a.Z, b.Z);
		EXPECT_EQ(a.W, b.W);
	}
	inline void ExpectNear(Quaternion a, Quaternion b)
	{
		EXPECT_NEAR(a.X, b.X, NearComparisonPrecision);
		EXPECT_NEAR(a.Y, b.Y, NearComparisonPrecision);
		EXPECT_NEAR(a.Z, b.Z, NearComparisonPrecision);
		EXPECT_NEAR(a.W, b.W, NearComparisonPrecision);
	}
}