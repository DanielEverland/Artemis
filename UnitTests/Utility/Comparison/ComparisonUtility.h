#pragma once

#define NearComparisonPrecision 1e-8

#define ExpectEqual(expectedValue, actualValue) \
	EXPECT_EQ(expectedValue, actualValue);

#define ExpectNotEqual(expectedValue, actualValue) \
	EXPECT_NE(expectedValue, actualValue);

#define ExpectNear(expectedValue, actualValue) \
	EXPECT_NEAR(expectedValue, actualValue, NearComparisonPrecision);

#define ExpectTrue(expression) \
	EXPECT_EQ(true, expression);

#define ExpectFalse(expression) \
	EXPECT_EQ(false, expression);

#define ExpectZero(value) \
	EXPECT_EQ(0, value);

#define ExpectThrow(expression, exception) \
	EXPECT_THROW(expression, exception);

#define ExpectAnyThrow(expression) \
	EXPECT_ANY_THROW(expression);