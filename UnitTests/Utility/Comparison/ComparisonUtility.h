#pragma once

#define TempExpectEqual(expectedValue, actualValue) EXPECT_EQ(expectedValue, actualValue);

namespace ArtemisEngine::UnitTests::Comparisons
{
	class ComparisonConstants
	{
	public:
		inline static const double nearComparisonPrecision = 1e-8;
	};

	template<class T>
	inline void ExpectZero(T value)
	{
		EXPECT_EQ(0, value);
	}
	inline void ExpectTrue(bool expression)
	{
		EXPECT_EQ(true, expression);
	}
	inline void ExpectFalse(bool expression)
	{
		EXPECT_EQ(false, expression);
	}
	inline void ExpectEqual(double a, double b)
	{
		EXPECT_EQ(a, b);
	}
	inline void ExpectNear(double a, double b)
	{
		EXPECT_NEAR(a, b, ComparisonConstants::nearComparisonPrecision);
	}
}