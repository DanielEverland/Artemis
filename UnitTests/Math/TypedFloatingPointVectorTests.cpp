#include "pch.h"

#include <map>

#include "Utility/Comparison/ComparisonUtilityVectors.h"
#include "Exceptions/DivideByZeroException.h"
#include "Exceptions/OutOfRangeException.h"
#include "Exceptions/NullReferenceException.h"
#include "Engine/Vector2.h"
#include "Engine/Vector3.h"
#include "Engine/Vector4.h"

#define Infinity std::numeric_limits<double>::infinity()

namespace Maths::Vectors
{
    using std::map;

    using ArtemisEngine::Vector2;
    using ArtemisEngine::Vector3;
    using ArtemisEngine::Vector4;

    const static int MaximumDimensions = 4;

    template <typename T>
    class TypedFloatingPointVectorTests : public ::testing::Test
    {
    };

    using MyTypes = ::testing::Types<Vector2, Vector3, Vector4>;
    TYPED_TEST_CASE(TypedFloatingPointVectorTests, MyTypes);

    TYPED_TEST(TypedFloatingPointVectorTests, CopyConstructor)
    {
        TypeParam expectedResult = TypeParam({ 2.53, 1.0, 0.2567, -1.5 });


        TypeParam actualResult = TypeParam(expectedResult);


        VectorExpectNear(expectedResult, actualResult);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, Indexing)
    {
        double expectedResult[MaximumDimensions]{ 2.53, 1.0, 0.2567, -1.5 };
        TypeParam actualResult({ 2.53, 1.0, 0.2567, -1.5 });


        for (unsigned int i = 0; i < actualResult.GetDimensions(); i++)
            TempExpectNear(expectedResult[i], actualResult[i]);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, ConstIndexing)
    {
        double expectedResult[MaximumDimensions]{ 2.53, 1.0, 0.2567, -1.5 };
        const TypeParam actualResult({ 2.53, 1.0, 0.2567, -1.5 });


        for (unsigned int i = 0; i < actualResult.GetDimensions(); i++)
            TempExpectNear(expectedResult[i], actualResult[i]);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, GetDotProduct)
    {
        TypeParam vectorA = TypeParam({ 2.53, 1.0, 0.2567, -1.5 });
        TypeParam vectorB = TypeParam({ 1.25, -2.25, 1.0, 5.25 });
        map<unsigned int, double> dotProducts
        {
            { 2, 0.9125 },
            { 3, 1.1692 },
            { 4, -6.7058 },
        };
        double expectedResult = dotProducts[vectorA.GetDimensions()];
        

        double actualResult = TypeParam::GetDotProduct(vectorA, vectorB);


        TempExpectNear(expectedResult, actualResult);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, GetAngle)
    {
        TypeParam vectorA = TypeParam({ 2.53, 1.0, 0.2567, -1.5 });
        TypeParam vectorB = TypeParam({ 1.25, -2.25, 1.0, 5.25 });
        map<unsigned int, double> angles
        {
            { 2, 82.51214821663946 },
            { 3, 81.08589268721897 },
            { 4, 111.2634002331296 },
        };
        double expectedResult = angles[vectorA.GetDimensions()];


        double actualResult = TypeParam::GetAngle(vectorA, vectorB);


        TempExpectNear(expectedResult, actualResult);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, SqrMagnitude)
    {
        TypeParam vector = TypeParam({ 2.53, 1.0, 0.2567, -1.5 });
        map<unsigned int, double> values
        {
            { 2, 7.400899999999991 },
            { 3, 7.466794889999999 },
            { 4, 9.716794889999999 },
        };
        double expectedResult = values[vector.GetDimensions()];


        double actualResult = vector.GetSqrMagnitude();


        TempExpectNear(expectedResult, actualResult);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, Magnitude)
    {
        TypeParam vector = TypeParam({ 2.53, 1.0, 0.2567, -1.5 });
        map<unsigned int, double> values
        {
            { 2, 2.7204595200076032 },
            { 3, 2.732543666622731 },
            { 4, 3.1171773914873691 },
        };
        double expectedResult = values[vector.GetDimensions()];


        double actualResult = vector.GetMagnitude();


        TempExpectNear(expectedResult, actualResult);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, NormalizedDivideByZero)
    {
        TypeParam vector = TypeParam();

        ExpectThrow(vector.GetNormalized(), DivideByZeroException);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, Normalized)
    {
        TypeParam vector = TypeParam({ 2.53, 1.0, 0.2567, -1.5 });
        map<unsigned int, Vector4> expectedVectors
        {
            { 2, Vector4(0.92998994522547751, 0.36758495858714529) },
            { 3, Vector4(0.92587724430656082, 0.36595938510140746, 0.093941774155531288) },
            { 4, Vector4(0.81163170466625378, 0.32080304532262999, 0.082350141734319121, -0.48120456798394501) },
        };
        TypeParam expectedResult = expectedVectors[vector.GetDimensions()];


        TypeParam actualResult = vector.GetNormalized();


        VectorExpectNear(expectedResult, actualResult);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, ToString)
    {
        TypeParam vector = TypeParam({ 2.53, 1.0, 0.2567, Math::Pi });
        map<unsigned int, string> expectedStrings
        {
            { 2, "(2.53, 1.0)" },
            { 3, "(2.53, 1.0, 0.2567)" },
            { 4, "(2.53, 1.0, 0.2567, 3.14159)" },
        };
        string expectedResult = expectedStrings[vector.GetDimensions()];


        string actualResult = vector.ToString();


        TempExpectEqual(expectedResult, actualResult);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, ToStringNaN)
    {
        TypeParam vector = TypeParam({ nan(""), nan(""), nan(""), nan("") });
        map<unsigned int, string> expectedStrings
        {
            { 2, "(NaN, NaN)" },
            { 3, "(NaN, NaN, NaN)" },
            { 4, "(NaN, NaN, NaN, NaN)" },
        };
        string expectedResult = expectedStrings[vector.GetDimensions()];


        string actualResult = vector.ToString();


        TempExpectEqual(expectedResult, actualResult);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, ToStringInfinity)
    {
        TypeParam vector = TypeParam({ Infinity, -Infinity, Infinity, -Infinity });
        map<unsigned int, string> expectedStrings
        {
            { 2, "(PositiveInfinity, NegativeInfinity)" },
            { 3, "(PositiveInfinity, NegativeInfinity, PositiveInfinity)" },
            { 4, "(PositiveInfinity, NegativeInfinity, PositiveInfinity, NegativeInfinity)" },
        };
        string expectedResult = expectedStrings[vector.GetDimensions()];


        string actualResult = vector.ToString();


        TempExpectEqual(expectedResult, actualResult);
    }


    TYPED_TEST(TypedFloatingPointVectorTests, AdditionOfTwoVectors)
    {
        TypeParam expectedResult({ 3.78, -1.25, 1.2567, 3.75 });
        TypeParam a({ 2.53, 1.0, 0.2567, -1.5 });
        TypeParam b({ 1.25, -2.25, 1.0, 5.25 });
        TypeParam actualResult;


        actualResult = a + b;


        VectorExpectNear(expectedResult, actualResult);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, AdditionAssignment)
    {
        TypeParam expectedResult({ 3.78, -1.25, 1.2567, 3.75 });
        TypeParam actualResult({ 2.53, 1.0, 0.2567, -1.5 });
        TypeParam b({ 1.25, -2.25, 1.0, 5.25 });


        actualResult += b;


        VectorExpectNear(expectedResult, actualResult);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarAddition)
    {
        TypeParam expectedResult({ 2.50, -1.0, 2.25, 6.50 });
        TypeParam actualResult({ 2.53, 1.0, 0.2567, -1.5 });
        TypeParam b({ 1.25, -2.25, 1.0, 5.25 });
        double scalar = 1.25;
        

        actualResult = b + scalar;


        VectorExpectNear(expectedResult, actualResult);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarAdditionAssignment)
    {
        TypeParam expectedResult({ 3.75, 0.25, 3.50, 7.75 });
        TypeParam actualResult({ 2.50, -1.0, 2.25, 6.50 });
        double scalar = 1.25;

        
        actualResult += scalar;


        VectorExpectNear(expectedResult, actualResult);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, SubtractionOfTwoVectors)
    {
        TypeParam expectedResult({ 1.25, 3.25, 0, -6.75 });
        TypeParam a({ 2.50, 1.0, 1.0, -1.5 });
        TypeParam b({ 1.25, -2.25, 1.0, 5.25 });
        TypeParam actualResult{ };


        actualResult = a - b;


        VectorExpectNear(expectedResult, actualResult);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, SubtractionAssignment)
    {
        TypeParam expectedResult({ 1.25, 3.25, 0, -6.75 });
        TypeParam actualResult({ 2.50, 1.0, 1.0, -1.5 });
        TypeParam b({ 1.25, -2.25, 1.0, 5.25 });
        

        actualResult -= b;


        VectorExpectNear(expectedResult, actualResult);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarSubtraction)
    {
        TypeParam actualResult{ };
        TypeParam expectedResult({ -0.25, -3.75, -0.5, 3.75 });
        TypeParam vector({ 1.25, -2.25, 1.0, 5.25 });
        double scalar = 1.5;


        actualResult = vector - scalar;


        VectorExpectNear(expectedResult, actualResult);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarSubtractionAssignment)
    {
        TypeParam expectedResult({ -0.25, -3.75, -0.5, 3.75 });
        TypeParam actualResult({ 1.25, -2.25, 1.0, 5.25 });
        double scalar = 1.5;


        actualResult -= scalar;


        VectorExpectNear(expectedResult, actualResult);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarMultiplication)
    {
        TypeParam expectedResult({ 1.875, -3.375, 1.5, 7.875 });
        TypeParam actualResult({ });
        TypeParam vector({ 1.25, -2.25, 1.0, 5.25 });
        double scalar = 1.5;

        
        actualResult = vector * scalar;


        VectorExpectNear(expectedResult, actualResult);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarMultiplicationAssignment)
    {
        TypeParam expectedResult({ 1.875, -3.375, 1.5, 7.875 });
        TypeParam actualResult({ 1.25, -2.25, 1.0, 5.25 });
        double scalar = 1.5;


        actualResult *= scalar;


        VectorExpectNear(expectedResult, actualResult);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, DivisionOfTwoVectors)
    {
        TypeParam expectedResult({ 2.0, -0.44444444444444442, 1.0, -0.2857142857142857 });
        TypeParam a({ 2.50, 1.0, 1.0, -1.5 });
        TypeParam b({ 1.25, -2.25, 1.0, 5.25 });
        TypeParam actualResult{ };


        actualResult = a / b;


        VectorExpectNear(expectedResult, actualResult);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, DivisionAssignment)
    {
        TypeParam expectedResult({ 2.0, -0.44444444444444442, 1.0, -0.2857142857142857 });
        TypeParam actualResult({ 2.50, 1.0, 1.0, -1.5 });
        TypeParam vector({ 1.25, -2.25, 1.0, 5.25 });


        actualResult /= vector;


        VectorExpectNear(expectedResult, actualResult);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarDivision)
    {
        TypeParam expectedResult({ 0.625, -1.125, 0.5, 2.625 });
        TypeParam actualResult;
        TypeParam vector({ 1.25, -2.25, 1.0, 5.25 });
        double scalar = 2.0;


        actualResult = vector / scalar;


        VectorExpectNear(expectedResult, actualResult);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarDivisionAssignment)
    {
        TypeParam expectedResult({ 0.625, -1.125, 0.5, 2.625 });
        TypeParam actualResult({ 1.25, -2.25, 1.0, 5.25 });
        double scalar = 2.0;


        actualResult /= scalar;


        VectorExpectNear(expectedResult, actualResult);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, Equality)
    {
        TypeParam a({ 2.53, 1.0, 0.2567, -1.5 });
        TypeParam b({ 2.53, 1.0, 0.2567, -1.5 });
        TypeParam c({ 1.25, -2.25, 1.0, 5.25 });
        

        TempExpectTrue(a == b);
        TempExpectFalse(a == c);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, Inequality)
    {
        TypeParam a({ 2.53, 1.0, 0.2567, -1.5 });
        TypeParam b({ 2.53, 1.0, 0.2567, -1.5 });
        TypeParam c({ 1.25, -2.25, 1.0, 5.25 });


        TempExpectFalse(a != b);
        TempExpectTrue(a != c);
    }
}
