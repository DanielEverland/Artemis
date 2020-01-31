#pragma once

namespace ArtemisEngine::UnitTests::Comparisons
{
	const double nearComparisonPrecision = 1e-8;

	void ExpectTrue(bool expression)
	{
		EXPECT_EQ(true, expression);
	}
	void ExpectFalse(bool expression)
	{
		EXPECT_EQ(false, expression);
	}
}