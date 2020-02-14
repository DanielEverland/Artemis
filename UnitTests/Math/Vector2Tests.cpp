#include "pch.h"

#include "Utility/Comparison/ComparisonUtility.h"
#include "Engine/Vector2.h"

namespace Maths::Vectors
{
    using ArtemisEngine::Vector2;

    TEST(Vector2, ConstructorXY)
    {
        Vector2 vector(10.0, 20.25);

        TempExpectNear(10.0, vector.X);
        TempExpectNear(20.25, vector.Y);
    }
    TEST(Vector2, InitializerListConstructor)
    {
        Vector2 vector({ 43.51, 2.0, 12.3 });

        TempExpectNear(43.51, vector.X);
        TempExpectNear(2.0, vector.Y);
    }
    TEST(Vector2, IntConstructorXY)
    {
        Vector2 vector(1, 2);

        TempExpectEqual(1, vector.X);
        TempExpectEqual(2, vector.Y);
    }
    TEST(Vector2, MemberAssignment)
    {
        Vector2 vector;

        vector.X = 5;
        vector.Y = 10;

        TempExpectEqual(5, vector.X);
        TempExpectEqual(10, vector.Y);
    }
}