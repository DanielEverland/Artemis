#include "pch.h"

#include <Core/Math.h>

TEST(MathTest, NotPowerOfTwo)
{
	ASSERT_FALSE(Math::IsPowerOfTwo(3));
}

TEST(MathTest, IsPowerOfTwo)
{
	ASSERT_TRUE(Math::IsPowerOfTwo(2));
}

TEST(MathTest, ZeroPowerOfTwo)
{
	ASSERT_FALSE(Math::IsPowerOfTwo(0));
}

TEST(MathTest, NegativePowerOfTwo)
{
	ASSERT_FALSE(Math::IsPowerOfTwo(-2));
}