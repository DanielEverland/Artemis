#include "gtest/gtest.h"
#include "pch.h"
//
//#include "Engine/Vector4.h"
//
//namespace Math::Vectors
//{
//    using ArtemisEngine::Vector4;
//
//    TEST(Vector4, ConstructorXY)
//    {
//        Vector4 vector(10.0, 20.25);
//
//        EXPECT_EQ(vector.x, 10.0);
//        EXPECT_EQ(vector.y, 20.25);
//    }
//    TEST(Vector4, ConstructorXYZ)
//    {
//        Vector4 vector(10.0, 20.25, 30.20);
//
//        EXPECT_EQ(vector.x, 10.0);
//        EXPECT_EQ(vector.y, 20.25);
//        EXPECT_EQ(vector.z, 30.20);
//    }
//    TEST(Vector4, ConstructorXYZW)
//    {
//        Vector4 vector(10.0, 20.25, 30.20, 40.12);
//
//        EXPECT_EQ(vector.x, 10.0);
//        EXPECT_EQ(vector.y, 20.25);
//        EXPECT_EQ(vector.z, 30.20);
//        EXPECT_EQ(vector.w, 40.12);
//    }
//    TEST(Vector4, IntConstructorXY)
//    {
//        Vector4 vector(1, 2);
//
//        EXPECT_EQ(vector.x, 1);
//        EXPECT_EQ(vector.y, 2);
//    }
//    TEST(Vector4, IntConstructorXYZ)
//    {
//        Vector4 vector(1, 2, 3);
//
//        EXPECT_EQ(vector.x, 1);
//        EXPECT_EQ(vector.y, 2);
//        EXPECT_EQ(vector.z, 3);
//    }
//    TEST(Vector4, IntConstructorXYZW)
//    {
//        Vector4 vector(1, 2, 3, 4);
//
//        EXPECT_EQ(vector.x, 1);
//        EXPECT_EQ(vector.y, 2);
//        EXPECT_EQ(vector.z, 3);
//        EXPECT_EQ(vector.w, 4);
//    }
//    TEST(Vector4, MemberAssignment)
//    {
//        Vector4 vector;
//
//        vector.x = 5;
//        vector.y = 10;
//        vector.z = 1;
//        vector.w = 100;
//
//        EXPECT_EQ(vector.x, 5);
//        EXPECT_EQ(vector.y, 10);
//        EXPECT_EQ(vector.z, 1);
//        EXPECT_EQ(vector.w, 100);
//    }
//}