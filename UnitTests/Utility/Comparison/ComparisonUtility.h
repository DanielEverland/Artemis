#pragma once

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
}