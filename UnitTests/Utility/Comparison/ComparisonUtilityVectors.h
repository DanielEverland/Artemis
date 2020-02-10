#pragma once

#include "ComparisonUtility.h"
#include "Engine/Maths/Vectors/VectorBase.h"

using ArtemisEngine::Maths::Vectors::VectorBase;

namespace ArtemisEngine::UnitTests::Comparisons
{
	template<class T, unsigned int dimensions>
	inline void ExpectNear(const VectorBase<T, dimensions>& a, const VectorBase<T, dimensions>& b)
	{
		EXPECT_NEAR(a.X, b.X, NearComparisonPrecision);
		EXPECT_NEAR(a.Y, b.Y, NearComparisonPrecision);
		EXPECT_NEAR(a.Z, b.Z, NearComparisonPrecision);
	}
}