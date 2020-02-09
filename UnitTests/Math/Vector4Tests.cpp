#include "gtest/gtest.h"
#include "pch.h"

#include "Engine/Vector4.h"

namespace Maths::Vectors
{
    using ArtemisEngine::Vector4;

    TEST(Vector4, ConstructorXY)
    {
        Vector4 vector(10.0, 20.25);

        EXPECT_EQ(10.0, vector.X);
        EXPECT_EQ(20.25, vector.Y);
    }
    TEST(Vector4, ConstructorXYZ)
    {
        Vector4 vector(10.0, 20.25, 30.20);

        EXPECT_EQ(10.0, vector.X);
        EXPECT_EQ(20.25, vector.Y);
        EXPECT_EQ(30.20, vector.Z);
    }
    TEST(Vector4, ConstructorXYZW)
    {
        Vector4 vector(10.0, 20.25, 30.20, 40.12);

        EXPECT_EQ(10.0, vector.X);
        EXPECT_EQ(20.25, vector.Y);
        EXPECT_EQ(30.20, vector.Z);
        EXPECT_EQ(40.12, vector.W);
    }
    TEST(Vector4, IntConstructorXY)
    {
        Vector4 vector(1, 2);

        EXPECT_EQ(1, vector.X);
        EXPECT_EQ(2, vector.Y);
    }
    TEST(Vector4, IntConstructorXYZ)
    {
        Vector4 vector(1, 2, 3);

        EXPECT_EQ(1, vector.X);
        EXPECT_EQ(2, vector.Y);
        EXPECT_EQ(3, vector.Z);
    }
    TEST(Vector4, IntConstructorXYZW)
    {
        Vector4 vector(1, 2, 3, 4);

        EXPECT_EQ(1, vector.X);
        EXPECT_EQ(2, vector.Y);
        EXPECT_EQ(3, vector.Z);
        EXPECT_EQ(4, vector.W);
    }
    TEST(Vector4, MemberAssignment)
    {
        Vector4 vector;

        vector.X = 5;
        vector.Y = 10;
        vector.Z = 1;
        vector.W = 100;

        EXPECT_EQ(5, vector.X);
        EXPECT_EQ(10, vector.Y);
        EXPECT_EQ(1, vector.Z);
        EXPECT_EQ(100, vector.W);
    }
}