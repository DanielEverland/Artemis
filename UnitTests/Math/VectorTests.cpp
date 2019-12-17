#include "pch.h"

#include <list>

#include "Engine/Vector2.h"
#include "Engine/Vector3.h"
#include "Engine/Vector4.h"

using ArtemisEngine::Vector2;
using ArtemisEngine::Vector3;
using ArtemisEngine::Vector4;

template <typename T>
class VectorTests : public ::testing::Test
{
public:
    const static int VectorsToInstantiate = 4;
    const static int ValuesPerSet = 4;
    const static int SetCount = 5;

    const static double VectorElementValues[SetCount][ValuesPerSet];
    
    T vectors[VectorsToInstantiate];

    void InitializeToDefaultValues(T vector, const double* const elements) const
    {
        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
            vector[i] = elements[i];
    }
};

template <typename T>
const double VectorTests<T>::VectorElementValues[SetCount][ValuesPerSet]
{
    { 2.5, 1.5, 0.25, -1.5 },
    { 1.25, -2.25, 1.0, 5.25 },
    { -0.75, 0.5, -3.75, -1.75 },
    { 3.0, 2.25, -4.75, 3.25 },
    { -1.25, -0.75, 2.75, 3.0 },
};


using MyTypes = ::testing::Types<Vector2, Vector3, Vector4>;
TYPED_TEST_CASE(VectorTests, MyTypes);


TYPED_TEST(VectorTests, Indexing)
{
    auto vector = this->vectors[0];
    const double* elementValues = VectorTests::VectorElementValues[0];


    this->InitializeToDefaultValues(vector, elementValues);


    for (unsigned int i = 0; i < vector.GetDimensions(); i++)
    {
        EXPECT_EQ(vector[i], elementValues[i]);
    }
}


TYPED_TEST(VectorTests, Addition)
{
    auto aVector = this->vectors[0];
    auto bVector = this->vectors[1];
    auto cVector = this->vectors[2];

    const double* aElementValues = VectorTests::VectorElementValues[0];
    const double* bElementValues = VectorTests::VectorElementValues[1];

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

    const double* aElementValues = VectorTests::VectorElementValues[0];
    const double* bElementValues = VectorTests::VectorElementValues[1];

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
    auto scalar = this->VectorElementValues[2][0];

    const double* vectorElementValues = VectorTests::VectorElementValues[1];

    this->InitializeToDefaultValues(bVector, vectorElementValues);


    aVector = bVector + scalar;


    for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
    {
        EXPECT_EQ(aVector[i], bVector[i] + scalar);
    }
}
TYPED_TEST(VectorTests, ScalarAdditionAssignment)
{
    auto vector = this->vectors[0];
    auto scalar = this->VectorElementValues[1][0];

    const double* vectorElementValues = VectorTests::VectorElementValues[0];

    this->InitializeToDefaultValues(vector, vectorElementValues);


    vector += scalar;

    
    for (unsigned int i = 0; i < vector.GetDimensions(); i++)
    {
        EXPECT_EQ(vector[i], vectorElementValues[i] + scalar);
    }
}