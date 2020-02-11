#include "gtest/gtest.h"
#include "pch.h"

#include "Engine/Vector3.h"

namespace Maths::Vectors
{
    using ArtemisEngine::Vector3;

    TEST(Vector3, ConstructorXY)
    {
        Vector3 vector(10.0, 20.25);

        EXPECT_EQ(10.0, vector.X);
        EXPECT_EQ(20.25, vector.Y);
    }
    TEST(Vector3, ConstructorXYZ)
    {
        Vector3 vector(10.0, 20.25, 30.20);

        EXPECT_EQ(10.0, vector.X);
        EXPECT_EQ(20.25, vector.Y);
        EXPECT_EQ(30.20, vector.Z);
    }
    TEST(Vector3, InitializerListConstructor)
    {
        Vector3 vector({ 43.51, 2.0, 12.3, 153.0154 });

        EXPECT_EQ(43.51, vector.X);
        EXPECT_EQ(2.0, vector.Y);
        EXPECT_EQ(12.3, vector.Z);
    }
    TEST(Vector3, IntConstructorXY)
    {
        Vector3 vector(1, 2);

        EXPECT_EQ(1, vector.X);
        EXPECT_EQ(2, vector.Y);
    }
    TEST(Vector3, IntConstructorXYZ)
    {
        Vector3 vector(1, 2, 3);

        EXPECT_EQ(1, vector.X);
        EXPECT_EQ(2, vector.Y);
        EXPECT_EQ(3, vector.Z);
    }
    TEST(Vector3, MemberAssignment)
    {
        Vector3 vector;

        vector.X = 5;
        vector.Y = 10;
        vector.Z = 1;

        EXPECT_EQ(5, vector.X);
        EXPECT_EQ(10, vector.Y);
        EXPECT_EQ(1, vector.Z);
    }
    TEST(Vector3, CrossProduct)
    {
        Vector3 a(1, 2, 3);
        Vector3 b(4, 5, 6);

        Vector3 c = Vector3::GetCrossProduct(a, b);

        EXPECT_EQ(-3, c.X);
        EXPECT_EQ(6, c.Y);
        EXPECT_EQ(-3, c.Z);
    }
}