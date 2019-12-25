#include "pch.h"

#include <iterator>
#include <list>
#include <map>

#include "Exceptions/DivideByZeroException.h"
#include "Exceptions/OutOfRangeException.h"
#include "Exceptions/NullReferenceException.h"
#include "Engine/Vector2.h"
#include "Engine/Vector3.h"
#include "Engine/Vector4.h"

namespace Math::Vectors
{
    using std::map;
    using std::list;

    using ArtemisEngine::Vector2;
    using ArtemisEngine::Vector3;
    using ArtemisEngine::Vector4;

#define Infinity std::numeric_limits<double>::infinity()

    const double FloatingPointComparisonPrecision = 0.00001;

    template <typename T>
    class TypedVectorTests : public ::testing::Test
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
    };

    template <typename T>
    const double TypedVectorTests<T>::ElementValues[SetCount][MaximumDimensions]
    {
        { 2.53, 1.0, 0.2567, -1.5 },
        { 1.25, -2.25, 1.0, 5.25 },
        { -0.75, 0.5, -3.75, -1.75 },
        { 3.0, 2.25, -4.75, 3.25 },
        { -1.25, -0.75, 2.75, 3.0 },
    };

    template <typename T>
    map<unsigned int, list<double>> TypedVectorTests<T>::ExpectedNormalizedValues
    {
        { 2, list<double> { 0.92998, 0.36758 } },
        { 3, list<double> { 0.92587, 0.36595, 0.09394 } },
        { 4, list<double> { 0.81163, 0.32080, 0.08235, -0.48120 } },
    };

    template <typename T>
    const double TypedVectorTests<T>::InfinityValues[MaximumDimensions]
    {
        Infinity, -Infinity, Infinity, -Infinity
    };

    template<typename T>
    map<unsigned int, string> TypedVectorTests<T>::ExpectedStrings
    {
        { 2, "(2.53, 1.0)" },
        { 3, "(2.53, 1.0, 0.2567)" },
        { 4, "(2.53, 1.0, 0.2567, -1.5)" },
    };

    template<typename T>
    map<unsigned int, string> TypedVectorTests<T>::ExpectedNaNStrings
    {
        { 2, "(NaN, NaN)" },
        { 3, "(NaN, NaN, NaN)" },
        { 4, "(NaN, NaN, NaN, NaN)" },
    };

    template<typename T>
    map<unsigned int, string> TypedVectorTests<T>::ExpectedInfinityStrings
    {
        { 2, "(PositiveInfinity, NegativeInfinity)" },
        { 3, "(PositiveInfinity, NegativeInfinity, PositiveInfinity)" },
        { 4, "(PositiveInfinity, NegativeInfinity, PositiveInfinity, NegativeInfinity)" },
    };

    template <typename T>
    map<unsigned int, double> TypedVectorTests<T>::ExpectedDotProduct
    {
        { 2, 0.9125 },
        { 3, 1.1692 },
        { 4, -6.7058 },
    };

    template<typename T>
    map<unsigned int, double> TypedVectorTests<T>::ExpectedMagnitude
    {
        { 2, 2.72045 },
        { 3, 2.73254 },
        { 4, 3.11717 },
    };

    template <typename T>
    map<unsigned int, double> TypedVectorTests<T>::ExpectedAngle
    {
        { 2, 82.51214 },
        { 3, 81.08589 },
        { 4, 111.26340 },
    };

    using MyTypes = ::testing::Types<Vector2, Vector3, Vector4>;
    TYPED_TEST_CASE(TypedVectorTests, MyTypes);

    TYPED_TEST(TypedVectorTests, EmptyConstructor)
    {
        auto vector = this->CallConstructorNoArguments();

        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(0, vector[i]);
        }
    }

    TYPED_TEST(TypedVectorTests, CopyConstructor)
    {
        auto copy = this->vectors[0];
        const double* elementValues = TypedVectorTests::ElementValues[0];

        auto vector = this->CallCopyConstructor(copy);

        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(copy[i], vector[i]);
        }
    }

    TYPED_TEST(TypedVectorTests, Indexing)
    {
        auto vector = this->vectors[0];
        const double* elementValues = TypedVectorTests::ElementValues[0];


        this->InitializeToDefaultValues(vector, elementValues);


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(vector[i], elementValues[i]);
        }
    }

    TYPED_TEST(TypedVectorTests, ConstIndexing)
    {
        const double* elementValues = TypedVectorTests::ElementValues[0];
        this->InitializeToDefaultValues(this->vectors[0], elementValues);


        const auto vector = this->vectors[0];


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(vector[i], elementValues[i]);
        }
    }

    TYPED_TEST(TypedVectorTests, DimensionIsPositive)
    {
        auto vector = this->vectors[0];

        EXPECT_LT(0, vector.GetDimensions());
    }

    TYPED_TEST(TypedVectorTests, IndexingOutOfRange)
    {
        auto vector = this->vectors[0];

        EXPECT_THROW(vector[-1] = 0, OutOfRangeException);
        EXPECT_THROW(vector[100] = 0, OutOfRangeException);
    }

    TYPED_TEST(TypedVectorTests, ConstIndexingOutOfRange)
    {
        auto const vector = this->vectors[0];

        EXPECT_THROW(vector[-1], OutOfRangeException);
        EXPECT_THROW(vector[100], OutOfRangeException);
    }

    TYPED_TEST(TypedVectorTests, GetDotProduct)
    {
        auto vectorA = this->vectors[0];
        auto vectorB = this->vectors[1];

        const double* elementValuesA = TypedVectorTests::ElementValues[0];
        const double* elementValuesB = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(vectorA, elementValuesA);
        this->InitializeToDefaultValues(vectorB, elementValuesB);



        double expectedValue = TypedVectorTests::ExpectedDotProduct[vectorA.GetDimensions()];
        double dotProduct = this->GetDotProduct(vectorA, vectorB);



        EXPECT_NEAR(expectedValue, dotProduct, FloatingPointComparisonPrecision);
    }

    TYPED_TEST(TypedVectorTests, GetAngle)
    {
        auto vectorA = this->vectors[0];
        auto vectorB = this->vectors[1];

        const double* elementValuesA = TypedVectorTests::ElementValues[0];
        const double* elementValuesB = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(vectorA, elementValuesA);
        this->InitializeToDefaultValues(vectorB, elementValuesB);



        double expectedAngle = TypedVectorTests::ExpectedAngle[vectorA.GetDimensions()];
        double actualAngle = this->GetAngle(vectorA, vectorB);



        EXPECT_NEAR(expectedAngle, actualAngle, FloatingPointComparisonPrecision);
    }

    TYPED_TEST(TypedVectorTests, SqrMagnitude)
    {
        auto vector = this->vectors[0];
        const double* elementValues = TypedVectorTests::ElementValues[0];

        TypedVectorTests::InitializeToDefaultValues(vector, elementValues);

        double vectorSqrMagnitude = vector.GetSqrMagnitude();

        double expectedValue = 0;
        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            expectedValue += vector[i] * vector[i];
        }


        EXPECT_NEAR(expectedValue, vectorSqrMagnitude, FloatingPointComparisonPrecision);
    }

    TYPED_TEST(TypedVectorTests, Magnitude)
    {
        auto vector = this->vectors[0];
        auto expectedValue = TypedVectorTests::ExpectedMagnitude[vector.GetDimensions()];
        const double* elementValues = TypedVectorTests::ElementValues[0];

        TypedVectorTests::InitializeToDefaultValues(vector, elementValues);


        auto magnitude = vector.GetMagnitude();


        EXPECT_NEAR(expectedValue, magnitude, FloatingPointComparisonPrecision);
    }

    TYPED_TEST(TypedVectorTests, NormalizedDivideByZero)
    {
        auto vector = this->vectors[0];

        EXPECT_THROW(vector.GetNormalized(), DivideByZeroException);
    }

    TYPED_TEST(TypedVectorTests, Normalized)
    {
        auto vector = this->vectors[0];
        list<double> expectedValues = TypedVectorTests::ExpectedNormalizedValues[vector.GetDimensions()];
        const double* elementValues = TypedVectorTests::ElementValues[0];

        TypedVectorTests::InitializeToDefaultValues(vector, elementValues);


        auto normalized = vector.GetNormalized();


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            auto iter = expectedValues.begin();
            std::advance(iter, i);

            EXPECT_NEAR(*iter, normalized[i], FloatingPointComparisonPrecision);
        }
    }

    TYPED_TEST(TypedVectorTests, ToString)
    {
        auto vector = this->vectors[0];
        string expectedString = TypedVectorTests::ExpectedStrings[vector.GetDimensions()];
        const double* elementValues = TypedVectorTests::ElementValues[0];

        this->InitializeToDefaultValues(vector, elementValues);


        auto vectorString = vector.ToString();


        EXPECT_EQ(expectedString, vectorString);
    }

    TYPED_TEST(TypedVectorTests, ToStringNaN)
    {
        auto vector = this->vectors[0];
        string expectedString = TypedVectorTests::ExpectedNaNStrings[vector.GetDimensions()];

        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
            vector[i] = nan("");


        string vectorString = vector.ToString();


        EXPECT_EQ(expectedString, vectorString);
    }

    TYPED_TEST(TypedVectorTests, ToStringInfinity)
    {
        auto vector = this->vectors[0];
        string expectedString = TypedVectorTests::ExpectedInfinityStrings[vector.GetDimensions()];

        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
            vector[i] = TypedVectorTests::InfinityValues[i];


        string vectorString = vector.ToString();


        EXPECT_EQ(expectedString, vectorString);
    }


    TYPED_TEST(TypedVectorTests, AdditionOfTwoVectors)
    {
        auto aVector = this->vectors[0];
        auto bVector = this->vectors[1];
        auto cVector = this->vectors[2];

        const double* aElementValues = TypedVectorTests::ElementValues[0];
        const double* bElementValues = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        cVector = aVector + bVector;


        for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
        {
            EXPECT_EQ(cVector[i], aElementValues[i] + bElementValues[i]);
        }
    }
    TYPED_TEST(TypedVectorTests, AdditionAssignment)
    {
        auto aVector = this->vectors[0];
        auto bVector = this->vectors[1];

        const double* aElementValues = TypedVectorTests::ElementValues[0];
        const double* bElementValues = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        aVector += bVector;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aVector[i], aElementValues[i] + bElementValues[i]);
        }
    }
    TYPED_TEST(TypedVectorTests, ScalarAddition)
    {
        auto aVector = this->vectors[0];
        auto bVector = this->vectors[1];
        auto scalar = this->ElementValues[2][0];

        const double* ElementValues = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(bVector, ElementValues);


        aVector = bVector + scalar;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aVector[i], bVector[i] + scalar);
        }
    }
    TYPED_TEST(TypedVectorTests, ScalarAdditionAssignment)
    {
        auto vector = this->vectors[0];
        auto scalar = this->ElementValues[1][0];

        const double* ElementValues = TypedVectorTests::ElementValues[0];

        this->InitializeToDefaultValues(vector, ElementValues);


        vector += scalar;


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(vector[i], ElementValues[i] + scalar);
        }
    }

    TYPED_TEST(TypedVectorTests, SubtractionOfTwoVectors)
    {
        auto aVector = this->vectors[0];
        auto bVector = this->vectors[1];
        auto cVector = this->vectors[2];

        const double* aElementValues = TypedVectorTests::ElementValues[0];
        const double* bElementValues = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        cVector = aVector - bVector;


        for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
        {
            EXPECT_EQ(cVector[i], aElementValues[i] - bElementValues[i]);
        }
    }
    TYPED_TEST(TypedVectorTests, SubtractionAssignment)
    {
        auto aVector = this->vectors[0];
        auto bVector = this->vectors[1];

        const double* aElementValues = TypedVectorTests::ElementValues[0];
        const double* bElementValues = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        aVector -= bVector;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aVector[i], aElementValues[i] - bElementValues[i]);
        }
    }
    TYPED_TEST(TypedVectorTests, ScalarSubtraction)
    {
        auto aVector = this->vectors[0];
        auto bVector = this->vectors[1];
        auto scalar = this->ElementValues[2][0];

        const double* ElementValues = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(bVector, ElementValues);


        aVector = bVector - scalar;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aVector[i], bVector[i] - scalar);
        }
    }
    TYPED_TEST(TypedVectorTests, ScalarSubtractionAssignment)
    {
        auto vector = this->vectors[0];
        auto scalar = this->ElementValues[1][0];

        const double* ElementValues = TypedVectorTests::ElementValues[0];

        this->InitializeToDefaultValues(vector, ElementValues);


        vector -= scalar;


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(vector[i], ElementValues[i] - scalar);
        }
    }

    TYPED_TEST(TypedVectorTests, MultiplicationOfTwoVectors)
    {
        auto aVector = this->vectors[0];
        auto bVector = this->vectors[1];
        auto cVector = this->vectors[2];

        const double* aElementValues = TypedVectorTests::ElementValues[0];
        const double* bElementValues = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        cVector = aVector * bVector;


        for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
        {
            EXPECT_EQ(cVector[i], aElementValues[i] * bElementValues[i]);
        }
    }
    TYPED_TEST(TypedVectorTests, MultiplicationAssignment)
    {
        auto aVector = this->vectors[0];
        auto bVector = this->vectors[1];

        const double* aElementValues = TypedVectorTests::ElementValues[0];
        const double* bElementValues = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        aVector *= bVector;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aVector[i], aElementValues[i] * bElementValues[i]);
        }
    }
    TYPED_TEST(TypedVectorTests, ScalarMultiplication)
    {
        auto aVector = this->vectors[0];
        auto bVector = this->vectors[1];
        auto scalar = this->ElementValues[2][0];

        const double* ElementValues = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(bVector, ElementValues);


        aVector = bVector * scalar;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aVector[i], bVector[i] * scalar);
        }
    }
    TYPED_TEST(TypedVectorTests, ScalarMultiplicationAssignment)
    {
        auto vector = this->vectors[0];
        auto scalar = this->ElementValues[1][0];

        const double* ElementValues = TypedVectorTests::ElementValues[0];

        this->InitializeToDefaultValues(vector, ElementValues);


        vector *= scalar;


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(vector[i], ElementValues[i] * scalar);
        }
    }

    TYPED_TEST(TypedVectorTests, DivisionOfTwoVectors)
    {
        auto aVector = this->vectors[0];
        auto bVector = this->vectors[1];
        auto cVector = this->vectors[2];

        const double* aElementValues = TypedVectorTests::ElementValues[0];
        const double* bElementValues = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        cVector = aVector / bVector;


        for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
        {
            EXPECT_EQ(cVector[i], aElementValues[i] / bElementValues[i]);
        }
    }
    TYPED_TEST(TypedVectorTests, DivisionAssignment)
    {
        auto aVector = this->vectors[0];
        auto bVector = this->vectors[1];

        const double* aElementValues = TypedVectorTests::ElementValues[0];
        const double* bElementValues = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(aVector, aElementValues);
        this->InitializeToDefaultValues(bVector, bElementValues);


        aVector /= bVector;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aVector[i], aElementValues[i] / bElementValues[i]);
        }
    }
    TYPED_TEST(TypedVectorTests, ScalarDivision)
    {
        auto aVector = this->vectors[0];
        auto bVector = this->vectors[1];
        auto scalar = this->ElementValues[2][0];

        const double* ElementValues = TypedVectorTests::ElementValues[1];

        this->InitializeToDefaultValues(bVector, ElementValues);


        aVector = bVector / scalar;


        for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
        {
            EXPECT_EQ(aVector[i], bVector[i] / scalar);
        }
    }
    TYPED_TEST(TypedVectorTests, ScalarDivisionAssignment)
    {
        auto vector = this->vectors[0];
        auto scalar = this->ElementValues[1][0];

        const double* ElementValues = TypedVectorTests::ElementValues[0];

        this->InitializeToDefaultValues(vector, ElementValues);


        vector /= scalar;


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(vector[i], ElementValues[i] / scalar);
        }
    }
}