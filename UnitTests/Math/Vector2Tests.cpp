#include "gtest/gtest.h"
#include "pch.h"

#include "Engine/Vector2.h"

namespace Maths::Vectors
{
    using ArtemisEngine::Vector2;

    TEST(Vector2, ConstructorXY)
    {
        Vector2 vector(10.0, 20.25);

        EXPECT_EQ(10.0, vector.x);
        EXPECT_EQ(20.25, vector.y);
    }
    TEST(Vector2, IntConstructorXY)
    {
        Vector2 vector(1, 2);

        EXPECT_EQ(1, vector.x);
        EXPECT_EQ(2, vector.y);
    }
    TEST(Vector2, MemberAssignment)
    {
        Vector2 vector;

        vector.x = 5;
        vector.y = 10;

        EXPECT_EQ(5, vector.x);
        EXPECT_EQ(10, vector.y);
    }
}