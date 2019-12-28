#include "gtest/gtest.h"
#include "pch.h"

#include "Engine/Math/Vectors/VectorBase.h"

using ArtemisEngine::Math::Vectors::VectorBase;

typedef VectorBase<double, 5> Vector;

TEST(ArbitraryVector, EmptyConstructor)
{
	Vector vector;

	for (unsigned int i = 0; i < 5; i++)
	{
		EXPECT_EQ(vector[i], 0);
	}
}
TEST(ArbitraryVector, Constructor)
{
	Vector vector({ 1, 2, 3, 4, 5 });

	EXPECT_EQ(vector[0], 1);
	EXPECT_EQ(vector[1], 2);
	EXPECT_EQ(vector[2], 3);
	EXPECT_EQ(vector[3], 4);
	EXPECT_EQ(vector[4], 5);
}
TEST(ArbitraryVector, ConstIndexer)
{
	Vector vector({ 1, 2, 3, 4, 5 });

	const Vector constVector = vector;

	EXPECT_EQ(constVector[0], 1);
	EXPECT_EQ(constVector[1], 2);
	EXPECT_EQ(constVector[2], 3);
	EXPECT_EQ(constVector[3], 4);
	EXPECT_EQ(constVector[4], 5);
}