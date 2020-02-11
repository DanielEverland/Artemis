#include "gtest/gtest.h"
#include "pch.h"

#include "Engine/Vector2.h"

namespace Maths::Vectors
{
    using ArtemisEngine::Vector2;

    TEST(Vector2, ConstructorXY)
    {
        Vector2 vector(10.0, 20.25);

        EXPECT_EQ(10.0, vector.X);
        EXPECT_EQ(20.25, vector.Y);
    }
    TEST(Vector2, InitializerListConstructor)
    {
        Vector2 vector({ 43.51, 2.0, 12.3 });

        EXPECT_EQ(43.51, vector.X);
        EXPECT_EQ(2.0, vector.Y);
    }
    TEST(Vector2, IntConstructorXY)
    {
        Vector2 vector(1, 2);

        EXPECT_EQ(1, vector.X);
        EXPECT_EQ(2, vector.Y);
    }
    TEST(Vector2, MemberAssignment)
    {
        Vector2 vector;

        vector.X = 5;
        vector.Y = 10;

        EXPECT_EQ(5, vector.X);
        EXPECT_EQ(10, vector.Y);
    }
}