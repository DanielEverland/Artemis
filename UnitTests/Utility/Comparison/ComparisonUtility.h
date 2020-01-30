#pragma once

namespace ArtemisEngine::UnitTests::Comparisons
{
	void ExpectTrue(bool expression)
	{
		EXPECT_EQ(true, expression);
	}
	void ExpectFalse(bool expression)
	{
		EXPECT_EQ(false, expression);
	}
}