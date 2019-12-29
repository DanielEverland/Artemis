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

	EXPECT_EQ(1, vector[0]);
	EXPECT_EQ(2, vector[1]);
	EXPECT_EQ(3, vector[2]);
	EXPECT_EQ(4, vector[3]);
	EXPECT_EQ(5, vector[4]);
}
TEST(ArbitraryVector, ConstIndexer)
{
	Vector vector({ 1, 2, 3, 4, 5 });

	const Vector constVector = vector;

	EXPECT_EQ(1, constVector[0]);
	EXPECT_EQ(2, constVector[1]);
	EXPECT_EQ(3, constVector[2]);
	EXPECT_EQ(4, constVector[3]);
	EXPECT_EQ(5, constVector[4]);
}