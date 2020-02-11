#include "pch.h"

#include <iterator>
#include <list>
#include <map>

#include "Utility/Comparison/ComparisonUtilityVectors.h"
#include "Exceptions/DivideByZeroException.h"
#include "Exceptions/OutOfRangeException.h"
#include "Exceptions/NullReferenceException.h"
#include "Engine/Vector2.h"
#include "Engine/Vector3.h"
#include "Engine/Vector4.h"

namespace Maths::Vectors
{
    using std::map;
    using std::list;

    using ArtemisEngine::Vector2;
    using ArtemisEngine::Vector3;
    using ArtemisEngine::Vector4;

#define Infinity std::numeric_limits<double>::infinity()

    const double FloatingPointComparisonPrecision = 0.00001;

    template <typename T>
    class TypedFloatingPointVectorTests : public ::testing::Test
    {
    public:

        const static int VectorsToInstantiate = 4;
        const static int MaximumDimensions = 4;
        const static int SetCount = 5;

        const static double ElementValues[SetCount][MaximumDimensions];
        const static double InfinityValues[MaximumDimensions];
        static map<unsigned int, list<double>> ExpectedNormalizedValues;
        static map<unsigned int, string> ExpectedStrings;
        static map<unsigned int, string> ExpectedNaNStrings;
        static map<unsigned int, string> ExpectedInfinityStrings;
        static map<unsigned int, double> ExpectedDotProduct;
        static map<unsigned int, double> ExpectedMagnitude;
        static map<unsigned int, double> ExpectedAngle;

        T vectors[VectorsToInstantiate];

        double GetDotProduct(T a, T b)
        {
            return T::GetDotProduct(a, b);
        }
        double GetAngle(T a, T b)
        {
            return T::GetAngle(a, b);
        }
        T CallConstructorNoArguments()
        {
            return T();
        }
        T CallCopyConstructor(const T& copy)
        {
            return T(copy);
        }
        void InitializeToDefaultValues(T& vector, const double* const elements) const
        {
            for (unsigned int i = 0; i < vector.GetDimensions(); i++)
                vector[i] = elements[i];
        }


        // NEW
        T Initialize(const double* const elements) const
        {
            T toReturn;

            for (unsigned int i = 0; i < toReturn.GetDimensions(); i++)
                toReturn[i] = elements[i];

            return toReturn;
        }
    };

    template <typename T>
    const double TypedFloatingPointVectorTests<T>::ElementValues[SetCount][MaximumDimensions]
    {
        { 2.53, 1.0, 0.2567, -1.5 },
        { 1.25, -2.25, 1.0, 5.25 },
        { -0.75, 0.5, -3.75, -1.75 },
        { 3.0, 2.25, -4.75, 3.25 },
        { -1.25, -0.75, 2.75, 3.0 },
    };

    template <typename T>
    map<unsigned int, list<double>> TypedFloatingPointVectorTests<T>::ExpectedNormalizedValues
    {
        { 2, list<double> { 0.92998, 0.36758 } },
        { 3, list<double> { 0.92587, 0.36595, 0.09394 } },
        { 4, list<double> { 0.81163, 0.32080, 0.08235, -0.48120 } },
    };

    template <typename T>
    const double TypedFloatingPointVectorTests<T>::InfinityValues[MaximumDimensions]
    {
        Infinity, -Infinity, Infinity, -Infinity
    };

    template<typename T>
    map<unsigned int, string> TypedFloatingPointVectorTests<T>::ExpectedStrings
    {
        { 2, "(2.53, 1.0)" },
        { 3, "(2.53, 1.0, 0.2567)" },
        { 4, "(2.53, 1.0, 0.2567, -1.5)" },
    };

    template<typename T>
    map<unsigned int, string> TypedFloatingPointVectorTests<T>::ExpectedNaNStrings
    {
        { 2, "(NaN, NaN)" },
        { 3, "(NaN, NaN, NaN)" },
        { 4, "(NaN, NaN, NaN, NaN)" },
    };

    template<typename T>
    map<unsigned int, string> TypedFloatingPointVectorTests<T>::ExpectedInfinityStrings
    {
        { 2, "(PositiveInfinity, NegativeInfinity)" },
        { 3, "(PositiveInfinity, NegativeInfinity, PositiveInfinity)" },
        { 4, "(PositiveInfinity, NegativeInfinity, PositiveInfinity, NegativeInfinity)" },
    };

    template <typename T>
    map<unsigned int, double> TypedFloatingPointVectorTests<T>::ExpectedDotProduct
    {
        { 2, 0.9125 },
        { 3, 1.1692 },
        { 4, -6.7058 },
    };

    template<typename T>
    map<unsigned int, double> TypedFloatingPointVectorTests<T>::ExpectedMagnitude
    {
        { 2, 2.72045 },
        { 3, 2.73254 },
        { 4, 3.11717 },
    };

    template <typename T>
    map<unsigned int, double> TypedFloatingPointVectorTests<T>::ExpectedAngle
    {
        { 2, 82.51214 },
        { 3, 81.08589 },
        { 4, 111.26340 },
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
        const double* elementValues = TypedFloatingPointVectorTests::ElementValues[0];
        this->InitializeToDefaultValues(this->vectors[0], elementValues);


        const TypeParam vector = this->vectors[0];


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(elementValues[i], vector[i]);
        }
    }

    TYPED_TEST(TypedFloatingPointVectorTests, GetDotProduct)
    {
        TypeParam vectorA = this->vectors[0];
        TypeParam vectorB = this->vectors[1];

        const double* elementValuesA = TypedFloatingPointVectorTests::ElementValues[0];
        const double* elementValuesB = TypedFloatingPointVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(vectorA, elementValuesA);
        this->InitializeToDefaultValues(vectorB, elementValuesB);



        double expectedValue = TypedFloatingPointVectorTests::ExpectedDotProduct[vectorA.GetDimensions()];
        double dotProduct = this->GetDotProduct(vectorA, vectorB);



        EXPECT_NEAR(expectedValue, dotProduct, FloatingPointComparisonPrecision);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, GetAngle)
    {
        TypeParam vectorA = this->vectors[0];
        TypeParam vectorB = this->vectors[1];

        const double* elementValuesA = TypedFloatingPointVectorTests::ElementValues[0];
        const double* elementValuesB = TypedFloatingPointVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(vectorA, elementValuesA);
        this->InitializeToDefaultValues(vectorB, elementValuesB);



        double expectedAngle = TypedFloatingPointVectorTests::ExpectedAngle[vectorA.GetDimensions()];
        double actualAngle = this->GetAngle(vectorA, vectorB);



        EXPECT_NEAR(expectedAngle, actualAngle, FloatingPointComparisonPrecision);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, SqrMagnitude)
    {
        TypeParam vector = this->vectors[0];
        const double* elementValues = TypedFloatingPointVectorTests::ElementValues[0];

        TypedFloatingPointVectorTests::InitializeToDefaultValues(vector, elementValues);

        double vectorSqrMagnitude = vector.GetSqrMagnitude();

        double expectedValue = 0;
        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            expectedValue += vector[i] * vector[i];
        }


        EXPECT_NEAR(expectedValue, vectorSqrMagnitude, FloatingPointComparisonPrecision);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, Magnitude)
    {
        TypeParam vector = this->vectors[0];
        double expectedValue = TypedFloatingPointVectorTests::ExpectedMagnitude[vector.GetDimensions()];
        const double* elementValues = TypedFloatingPointVectorTests::ElementValues[0];

        TypedFloatingPointVectorTests::InitializeToDefaultValues(vector, elementValues);


        double magnitude = vector.GetMagnitude();


        EXPECT_NEAR(expectedValue, magnitude, FloatingPointComparisonPrecision);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, NormalizedDivideByZero)
    {
        TypeParam vector = this->vectors[0];

        EXPECT_THROW(vector.GetNormalized(), DivideByZeroException);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, Normalized)
    {
        TypeParam vector = this->vectors[0];
        list<double> expectedValues = TypedFloatingPointVectorTests::ExpectedNormalizedValues[vector.GetDimensions()];
        const double* elementValues = TypedFloatingPointVectorTests::ElementValues[0];

        TypedFloatingPointVectorTests::InitializeToDefaultValues(vector, elementValues);


        TypeParam normalized = vector.GetNormalized();


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            auto iter = expectedValues.begin();
            std::advance(iter, i);

            EXPECT_NEAR(*iter, normalized[i], FloatingPointComparisonPrecision);
        }
    }

    TYPED_TEST(TypedFloatingPointVectorTests, ToString)
    {
        TypeParam vector = this->vectors[0];
        string expectedString = TypedFloatingPointVectorTests::ExpectedStrings[vector.GetDimensions()];
        const double* elementValues = TypedFloatingPointVectorTests::ElementValues[0];

        this->InitializeToDefaultValues(vector, elementValues);


        string vectorString = vector.ToString();


        EXPECT_EQ(expectedString, vectorString);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, ToStringNaN)
    {
        TypeParam vector = this->vectors[0];
        string expectedString = TypedFloatingPointVectorTests::ExpectedNaNStrings[vector.GetDimensions()];

        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
            vector[i] = nan("");


        string vectorString = vector.ToString();


        EXPECT_EQ(expectedString, vectorString);
    }

    TYPED_TEST(TypedFloatingPointVectorTests, ToStringInfinity)
    {
        TypeParam vector = this->vectors[0];
        string expectedString = TypedFloatingPointVectorTests::ExpectedInfinityStrings[vector.GetDimensions()];

        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
            vector[i] = TypedFloatingPointVectorTests::InfinityValues[i];


        string vectorString = vector.ToString();


        EXPECT_EQ(expectedString, vectorString);
    }


    TYPED_TEST(TypedFloatingPointVectorTests, AdditionOfTwoVectors)
    {
        TypeParam aVector = this->vectors[0];
        TypeParam bVector = this->vectors[1];
        TypeParam cVector = this->vectors[2];

        const double* aElementValues = TypedFloatingPointVectorTests::ElementValues[0];
        const double* bElementValues = TypedFloatingPointVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        cVector = aVector + bVector;


        for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aElementValues[i] + bElementValues[i], cVector[i]);
        }
    }
    TYPED_TEST(TypedFloatingPointVectorTests, AdditionAssignment)
    {
        TypeParam aVector = this->vectors[0];
        TypeParam bVector = this->vectors[1];

        const double* aElementValues = TypedFloatingPointVectorTests::ElementValues[0];
        const double* bElementValues = TypedFloatingPointVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        aVector += bVector;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aElementValues[i] + bElementValues[i], aVector[i]);
        }
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarAddition)
    {
        TypeParam aVector = this->vectors[0];
        TypeParam bVector = this->vectors[1];
        double scalar = this->ElementValues[2][0];

        const double* ElementValues = TypedFloatingPointVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(bVector, ElementValues);


        aVector = bVector + scalar;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(bVector[i] + scalar, aVector[i]);
        }
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarAdditionAssignment)
    {
        TypeParam vector = this->vectors[0];
        double scalar = this->ElementValues[1][0];

        const double* ElementValues = TypedFloatingPointVectorTests::ElementValues[0];

        this->InitializeToDefaultValues(vector, ElementValues);


        vector += scalar;


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(ElementValues[i] + scalar, vector[i]);
        }
    }

    TYPED_TEST(TypedFloatingPointVectorTests, SubtractionOfTwoVectors)
    {
        TypeParam aVector = this->vectors[0];
        TypeParam bVector = this->vectors[1];
        TypeParam cVector = this->vectors[2];

        const double* aElementValues = TypedFloatingPointVectorTests::ElementValues[0];
        const double* bElementValues = TypedFloatingPointVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        cVector = aVector - bVector;


        for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aElementValues[i] - bElementValues[i], cVector[i]);
        }
    }
    TYPED_TEST(TypedFloatingPointVectorTests, SubtractionAssignment)
    {
        TypeParam aVector = this->vectors[0];
        TypeParam bVector = this->vectors[1];

        const double* aElementValues = TypedFloatingPointVectorTests::ElementValues[0];
        const double* bElementValues = TypedFloatingPointVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        aVector -= bVector;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aElementValues[i] - bElementValues[i], aVector[i]);
        }
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarSubtraction)
    {
        TypeParam aVector = this->vectors[0];
        TypeParam bVector = this->vectors[1];
        double scalar = this->ElementValues[2][0];

        const double* ElementValues = TypedFloatingPointVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(bVector, ElementValues);


        aVector = bVector - scalar;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(bVector[i] - scalar, aVector[i]);
        }
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarSubtractionAssignment)
    {
        TypeParam vector = this->vectors[0];
        double scalar = this->ElementValues[1][0];

        const double* ElementValues = TypedFloatingPointVectorTests::ElementValues[0];

        this->InitializeToDefaultValues(vector, ElementValues);


        vector -= scalar;


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(ElementValues[i] - scalar, vector[i]);
        }
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarMultiplication)
    {
        TypeParam aVector = this->vectors[0];
        TypeParam bVector = this->vectors[1];
        double scalar = this->ElementValues[2][0];

        const double* ElementValues = TypedFloatingPointVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(bVector, ElementValues);


        aVector = bVector * scalar;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(bVector[i] * scalar, aVector[i]);
        }
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarMultiplicationAssignment)
    {
        TypeParam vector = this->vectors[0];
        double scalar = this->ElementValues[1][0];

        const double* ElementValues = TypedFloatingPointVectorTests::ElementValues[0];

        this->InitializeToDefaultValues(vector, ElementValues);


        vector *= scalar;


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(ElementValues[i] * scalar, vector[i]);
        }
    }

    TYPED_TEST(TypedFloatingPointVectorTests, DivisionOfTwoVectors)
    {
        TypeParam aVector = this->vectors[0];
        TypeParam bVector = this->vectors[1];
        TypeParam cVector = this->vectors[2];

        const double* aElementValues = TypedFloatingPointVectorTests::ElementValues[0];
        const double* bElementValues = TypedFloatingPointVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        cVector = aVector / bVector;


        for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aElementValues[i] / bElementValues[i], cVector[i]);
        }
    }
    TYPED_TEST(TypedFloatingPointVectorTests, DivisionAssignment)
    {
        TypeParam aVector = this->vectors[0];
        TypeParam bVector = this->vectors[1];

        const double* aElementValues = TypedFloatingPointVectorTests::ElementValues[0];
        const double* bElementValues = TypedFloatingPointVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        aVector /= bVector;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aElementValues[i] / bElementValues[i], aVector[i]);
        }
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarDivision)
    {
        TypeParam aVector = this->vectors[0];
        TypeParam bVector = this->vectors[1];
        double scalar = this->ElementValues[2][0];

        const double* ElementValues = TypedFloatingPointVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(bVector, ElementValues);


        aVector = bVector / scalar;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(bVector[i] / scalar, aVector[i]);
        }
    }
    TYPED_TEST(TypedFloatingPointVectorTests, ScalarDivisionAssignment)
    {
        TypeParam vector = this->vectors[0];
        double scalar = this->ElementValues[1][0];

        const double* ElementValues = TypedFloatingPointVectorTests::ElementValues[0];

        this->InitializeToDefaultValues(vector, ElementValues);


        vector /= scalar;


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(ElementValues[i] / scalar, vector[i]);
        }
    }
    TYPED_TEST(TypedFloatingPointVectorTests, Equality)
    {
        const double* aElementValues = TypedFloatingPointVectorTests::ElementValues[0];
        const double* bElementValues = TypedFloatingPointVectorTests::ElementValues[0];
        const double* cElementValues = TypedFloatingPointVectorTests::ElementValues[1];

        TypeParam a = this->vectors[0];
        TypeParam b = this->vectors[0];
        TypeParam c = this->vectors[1];

        this->InitializeToDefaultValues(a, aElementValues);
        this->InitializeToDefaultValues(b, bElementValues);
        this->InitializeToDefaultValues(c, cElementValues);

        EXPECT_EQ(true, a == b);
        EXPECT_EQ(false, a == c);
    }
    TYPED_TEST(TypedFloatingPointVectorTests, Inequality)
    {
        const double* aElementValues = TypedFloatingPointVectorTests::ElementValues[0];
        const double* bElementValues = TypedFloatingPointVectorTests::ElementValues[0];
        const double* cElementValues = TypedFloatingPointVectorTests::ElementValues[1];

        TypeParam a = this->vectors[0];
        TypeParam b = this->vectors[0];
        TypeParam c = this->vectors[1];

        this->InitializeToDefaultValues(a, aElementValues);
        this->InitializeToDefaultValues(b, bElementValues);
        this->InitializeToDefaultValues(c, cElementValues);

        EXPECT_EQ(false, a != b);
        EXPECT_EQ(true, a != c);
    }
}
