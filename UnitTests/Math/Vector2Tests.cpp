#include "pch.h"

#include "Utility/Comparison/ComparisonUtility.h"
#include "Include/Game/Vector2.h"

namespace Maths::Vectors
{
    using ArtemisEngine::Vector2;

    TEST(Vector2, ConstructorXY)
    {
        Vector2 vector(10.0, 20.25);


        ExpectNear(10.0, vector.X);
        ExpectNear(20.25, vector.Y);
    }
    TEST(Vector2, InitializerListConstructor)
    {
        Vector2 vector({ 43.51, 2.0, 12.3 });


        ExpectNear(43.51, vector.X);
        ExpectNear(2.0, vector.Y);
    }
    TEST(Vector2, IntConstructorXY)
    {
        Vector2 vector(1, 2);


        ExpectEqual(1, vector.X);
        ExpectEqual(2, vector.Y);
    }
    TEST(Vector2, MemberAssignment)
    {
        Vector2 vector;


        vector.X = 5;
        vector.Y = 10;


        ExpectEqual(5, vector.X);
        ExpectEqual(10, vector.Y);
    }
}