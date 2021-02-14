#include "pch.h"

#include <numbers>
#include <Core/Core/Vector.h>

TEST(Vectors, EmptyConstructor)
{
	Vector v;
	EXPECT_EQ(v.X, 0.0);
	EXPECT_EQ(v.Y, 0.0);
}

TEST(Vectors, Constructor)
{
	double x = 1.34565;
	double y = std::numbers::pi;

	Vector v(x, y);

	EXPECT_EQ(v.X, x);
	EXPECT_EQ(v.Y, y);
}

TEST(Vectors, ToString)
{
	double x = 121.34565;
	double y = std::numbers::pi;

	Vector v(x, y);

	EXPECT_EQ("(121.35, 3.14)", v.ToString());
}

TEST(Vectors, Equality)
{
	double x = 121.34565;
	double y = std::numbers::pi;

	Vector a(x, y);
	Vector b(x, y);

	EXPECT_EQ(a, b);
}

TEST(Vectors, Inequality)
{
	double ax = 121.34565;
	double bx = ax + 1e-10;
	double y = std::numbers::pi;

	Vector a(ax, y);
	Vector b(bx, y);

	EXPECT_NE(a, b);
}