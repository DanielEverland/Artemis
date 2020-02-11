#pragma once

#define NearComparisonPrecision 1e-8

#define TempExpectEqual(expectedValue, actualValue) \
	EXPECT_EQ(expectedValue, actualValue);

#define TempExpectNear(expectedValue, actualValue) \
	EXPECT_NEAR(expectedValue, actualValue, NearComparisonPrecision);

#define TempExpectTrue(expression) \
	EXPECT_EQ(true, expression);

#define TempExpectFalse(expression) \
	EXPECT_EQ(false, expression);

#define TempExpectZero(value) \
	EXPECT_EQ(0, value);


namespace ArtemisEngine::UnitTests::Comparisons
{
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
		TempExpectNear(a, b);
	}
}