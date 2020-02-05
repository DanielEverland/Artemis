#pragma once

#include "ComparisonUtility.h"
#include "Engine/Maths/Vectors/VectorBase.h"

using ArtemisEngine::Maths::Vectors::VectorBase;

namespace ArtemisEngine::UnitTests::Comparisons
{
	template<class T, unsigned int dimensions>
	inline void ExpectNear(const VectorBase<T, dimensions>& a, const VectorBase<T, dimensions>& b)
	{
		for (unsigned int i = 0; i < a.GetDimensions(); i++)
		{
			EXPECT_NEAR(a[i], b[i], ComparisonConstants::nearComparisonPrecision);
		}
	}
}