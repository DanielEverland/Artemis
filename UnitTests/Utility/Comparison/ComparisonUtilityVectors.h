#pragma once

#include "ComparisonUtility.h"
#include "Engine/Maths/Vectors/VectorBase.h"

using ArtemisEngine::Maths::Vectors::VectorBase;

namespace ArtemisEngine::UnitTests::Comparisons
{
	template<class T, unsigned int dimensions>
	inline void ExpectNear(const VectorBase<T, dimensions>& a, const VectorBase<T, dimensions>& b)
	{
		EXPECT_NEAR(a.x, b.x, ComparisonConstants::nearComparisonPrecision);
		EXPECT_NEAR(a.y, b.y, ComparisonConstants::nearComparisonPrecision);
		EXPECT_NEAR(a.z, b.z, ComparisonConstants::nearComparisonPrecision);
	}
}