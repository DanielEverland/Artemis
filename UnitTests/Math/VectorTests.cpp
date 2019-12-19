#include "pch.h"

#include <list>
#include <map>

#include "Engine/Vector2.h"
#include "Engine/Vector3.h"
#include "Engine/Vector4.h"

using std::map;

using ArtemisEngine::Vector2;
using ArtemisEngine::Vector3;
using ArtemisEngine::Vector4;

#define Infinity std::numeric_limits<double>::infinity()

template <typename T>
class VectorTests : public ::testing::Test
{
public:
    const static int VectorsToInstantiate = 4;
    const static int MaximumDimensions = 4;
    const static int SetCount = 5;

    const static double ElementValues[SetCount][MaximumDimensions];
    const static double InfinityValues[MaximumDimensions];
    static map<unsigned int, string> ExpectedStrings;
    static map<unsigned int, string> ExpectedNaNStrings;
    static map<unsigned int, string> ExpectedInfinityStrings;
    
    T vectors[VectorsToInstantiate];

    void InitializeToDefaultValues(T& vector, const double* const elements) const
    {
        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
            vector[i] = elements[i];
    }
};

template <typename T>
const double VectorTests<T>::ElementValues[SetCount][MaximumDimensions]
{
    { 2.53, 1.0, 0.2567, -1.5 },
    { 1.25, -2.25, 1.0, 5.25 },
    { -0.75, 0.5, -3.75, -1.75 },
    { 3.0, 2.25, -4.75, 3.25 },
    { -1.25, -0.75, 2.75, 3.0 },
};

template <typename T>
const double VectorTests<T>::InfinityValues[MaximumDimensions]
{
    Infinity, -Infinity, Infinity, -Infinity
};

template<typename T>
map<unsigned int, string> VectorTests<T>::ExpectedStrings
{
    { 2, "(2.53, 1.0)" },
    { 3, "(2.53, 1.0, 0.2567)" },
    { 4, "(2.53, 1.0, 0.2567, -1.5)" },
};

template<typename T>
map<unsigned int, string> VectorTests<T>::ExpectedNaNStrings
{
    { 2, "(NaN, NaN)" },
    { 3, "(NaN, NaN, NaN)" },
    { 4, "(NaN, NaN, NaN, NaN)" },
};

template<typename T>
map<unsigned int, string> VectorTests<T>::ExpectedInfinityStrings
{
    { 2, "(PositiveInfinity, NegativeInfinity)" },
    { 3, "(PositiveInfinity, NegativeInfinity, PositiveInfinity)" },
    { 4, "(PositiveInfinity, NegativeInfinity, PositiveInfinity, NegativeInfinity)" },
};

using MyTypes = ::testing::Types<Vector2, Vector3, Vector4>;
TYPED_TEST_CASE(VectorTests, MyTypes);


TYPED_TEST(VectorTests, Indexing)
{
    auto vector = this->vectors[0];
    const double* elementValues = VectorTests::ElementValues[0];


    this->InitializeToDefaultValues(vector, elementValues);


    for (unsigned int i = 0; i < vector.GetDimensions(); i++)
    {
        EXPECT_EQ(vector[i], elementValues[i]);
    }
}

TYPED_TEST(VectorTests, ToString)
{
    auto vector = this->vectors[0];
    string expectedString = VectorTests::ExpectedStrings[vector.GetDimensions()];
    const double* elementValues = VectorTests::ElementValues[0];

    this->InitializeToDefaultValues(vector, elementValues);


    auto vectorString = vector.ToString();


    EXPECT_EQ(expectedString, vectorString);
}

TYPED_TEST(VectorTests, ToStringNaN)
{
    auto vector = this->vectors[0];
    string expectedString = VectorTests::ExpectedNaNStrings[vector.GetDimensions()];

    for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        vector[i] = nan("");

    
    string vectorString = vector.ToString();


    EXPECT_EQ(expectedString, vectorString);
}

TYPED_TEST(VectorTests, ToStringInfinity)
{
    auto vector = this->vectors[0];
    string expectedString = VectorTests::ExpectedInfinityStrings[vector.GetDimensions()];

    for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        vector[i] = VectorTests::InfinityValues[i];


    string vectorString = vector.ToString();


    EXPECT_EQ(expectedString, vectorString);
}


TYPED_TEST(VectorTests, AdditionOfTwoVectors)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];
    auto cVector = this->vectors[2];

    const double* aElementValues = VectorTests::ElementValues[0];
    const double* bElementValues = VectorTests::ElementValues[1];

    this->InitializeToDefaultValues(aVector, aElementValues);
    this->InitializeToDefaultValues(bVector, bElementValues);


    cVector = aVector + bVector;


    for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
    {
        EXPECT_EQ(cVector[i], aElementValues[i] + bElementValues[i]);
    }
}
TYPED_TEST(VectorTests, AdditionAssignment)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];

    const double* aElementValues = VectorTests::ElementValues[0];
    const double* bElementValues = VectorTests::ElementValues[1];

    this->InitializeToDefaultValues(aVector, aElementValues);
    this->InitializeToDefaultValues(bVector, bElementValues);


    aVector += bVector;


    for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
    {
        EXPECT_EQ(aVector[i], aElementValues[i] + bElementValues[i]);
    }
}
TYPED_TEST(VectorTests, ScalarAddition)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];
    auto scalar = this->ElementValues[2][0];

    const double* ElementValues = VectorTests::ElementValues[1];

    this->InitializeToDefaultValues(bVector, ElementValues);


    aVector = bVector + scalar;


    for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
    {
        EXPECT_EQ(aVector[i], bVector[i] + scalar);
    }
}
TYPED_TEST(VectorTests, ScalarAdditionAssignment)
{
    auto vector = this->vectors[0];
    auto scalar = this->ElementValues[1][0];

    const double* ElementValues = VectorTests::ElementValues[0];

    this->InitializeToDefaultValues(vector, ElementValues);


    vector += scalar;

    
    for (unsigned int i = 0; i < vector.GetDimensions(); i++)
    {
        EXPECT_EQ(vector[i], ElementValues[i] + scalar);
    }
}

TYPED_TEST(VectorTests, SubtractionOfTwoVectors)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];
    auto cVector = this->vectors[2];

    const double* aElementValues = VectorTests::ElementValues[0];
    const double* bElementValues = VectorTests::ElementValues[1];

    this->InitializeToDefaultValues(aVector, aElementValues);
    this->InitializeToDefaultValues(bVector, bElementValues);


    cVector = aVector - bVector;


    for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
    {
        EXPECT_EQ(cVector[i], aElementValues[i] - bElementValues[i]);
    }
}
TYPED_TEST(VectorTests, SubtractionAssignment)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];

    const double* aElementValues = VectorTests::ElementValues[0];
    const double* bElementValues = VectorTests::ElementValues[1];

    this->InitializeToDefaultValues(aVector, aElementValues);
    this->InitializeToDefaultValues(bVector, bElementValues);


    aVector -= bVector;


    for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
    {
        EXPECT_EQ(aVector[i], aElementValues[i] - bElementValues[i]);
    }
}
TYPED_TEST(VectorTests, ScalarSubtraction)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];
    auto scalar = this->ElementValues[2][0];

    const double* ElementValues = VectorTests::ElementValues[1];

    this->InitializeToDefaultValues(bVector, ElementValues);


    aVector = bVector - scalar;


    for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
    {
        EXPECT_EQ(aVector[i], bVector[i] - scalar);
    }
}
TYPED_TEST(VectorTests, ScalarSubtractionAssignment)
{
    auto vector = this->vectors[0];
    auto scalar = this->ElementValues[1][0];

    const double* ElementValues = VectorTests::ElementValues[0];

    this->InitializeToDefaultValues(vector, ElementValues);


    vector -= scalar;


    for (unsigned int i = 0; i < vector.GetDimensions(); i++)
    {
        EXPECT_EQ(vector[i], ElementValues[i] - scalar);
    }
}

TYPED_TEST(VectorTests, MultiplicationOfTwoVectors)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];
    auto cVector = this->vectors[2];

    const double* aElementValues = VectorTests::ElementValues[0];
    const double* bElementValues = VectorTests::ElementValues[1];

    this->InitializeToDefaultValues(aVector, aElementValues);
    this->InitializeToDefaultValues(bVector, bElementValues);


    cVector = aVector * bVector;


    for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
    {
        EXPECT_EQ(cVector[i], aElementValues[i] * bElementValues[i]);
    }
}
TYPED_TEST(VectorTests, MultiplicationAssignment)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];

    const double* aElementValues = VectorTests::ElementValues[0];
    const double* bElementValues = VectorTests::ElementValues[1];

    this->InitializeToDefaultValues(aVector, aElementValues);
    this->InitializeToDefaultValues(bVector, bElementValues);


    aVector *= bVector;


    for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
    {
        EXPECT_EQ(aVector[i], aElementValues[i] * bElementValues[i]);
    }
}
TYPED_TEST(VectorTests, ScalarMultiplication)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];
    auto scalar = this->ElementValues[2][0];

    const double* ElementValues = VectorTests::ElementValues[1];

    this->InitializeToDefaultValues(bVector, ElementValues);


    aVector = bVector * scalar;


    for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
    {
        EXPECT_EQ(aVector[i], bVector[i] * scalar);
    }
}
TYPED_TEST(VectorTests, ScalarMultiplicationAssignment)
{
    auto vector = this->vectors[0];
    auto scalar = this->ElementValues[1][0];

    const double* ElementValues = VectorTests::ElementValues[0];

    this->InitializeToDefaultValues(vector, ElementValues);


    vector *= scalar;


    for (unsigned int i = 0; i < vector.GetDimensions(); i++)
    {
        EXPECT_EQ(vector[i], ElementValues[i] * scalar);
    }
}

TYPED_TEST(VectorTests, DivisionOfTwoVectors)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];
    auto cVector = this->vectors[2];

    const double* aElementValues = VectorTests::ElementValues[0];
    const double* bElementValues = VectorTests::ElementValues[1];

    this->InitializeToDefaultValues(aVector, aElementValues);
    this->InitializeToDefaultValues(bVector, bElementValues);


    cVector = aVector / bVector;


    for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
    {
        EXPECT_EQ(cVector[i], aElementValues[i] / bElementValues[i]);
    }
}
TYPED_TEST(VectorTests, DivisionAssignment)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];

    const double* aElementValues = VectorTests::ElementValues[0];
    const double* bElementValues = VectorTests::ElementValues[1];

    this->InitializeToDefaultValues(aVector, aElementValues);
    this->InitializeToDefaultValues(bVector, bElementValues);


    aVector /= bVector;


    for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
    {
        EXPECT_EQ(aVector[i], aElementValues[i] / bElementValues[i]);
    }
}
TYPED_TEST(VectorTests, ScalarDivision)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];
    auto scalar = this->ElementValues[2][0];

    const double* ElementValues = VectorTests::ElementValues[1];

    this->InitializeToDefaultValues(bVector, ElementValues);


    aVector = bVector / scalar;


    for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
    {
        EXPECT_EQ(aVector[i], bVector[i] / scalar);
    }
}
TYPED_TEST(VectorTests, ScalarDivisionAssignment)
{
    auto vector = this->vectors[0];
    auto scalar = this->ElementValues[1][0];

    const double* ElementValues = VectorTests::ElementValues[0];

    this->InitializeToDefaultValues(vector, ElementValues);


    vector /= scalar;


    for (unsigned int i = 0; i < vector.GetDimensions(); i++)
    {
        EXPECT_EQ(vector[i], ElementValues[i] / scalar);
    }
}