#include "pch.h"

#include <list>

#include "Engine/Vector2.h"
#include "Engine/Vector3.h"
#include "Engine/Vector4.h"

using ArtemisEngine::Vector2;
using ArtemisEngine::Vector3;
using ArtemisEngine::Vector4;

template <typename T>
class VectorTests : public ::testing::Test, public ::testing::Environment
{
public:

    const static int ValuesPerSet = 4;
    const static int SetCount = 5;

    const static double VectorElementValues[SetCount][ValuesPerSet];

    T firstVector;
    T secondVector;

    VectorTests()
    {
        for (unsigned int i = 0; i < firstVector.GetDimensions(); i++)
        {
            firstVector[i] = VectorElementValues[0][i];
        }

        for (unsigned int i = 0; i < secondVector.GetDimensions(); i++)
        {
            secondVector[i] = VectorElementValues[1][i];
        }
    }

    T CreateInstance() const;
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

template<typename T>
T VectorTests<T>::CreateInstance() const
{
    return T();
}


using MyTypes = ::testing::Types<Vector2, Vector3, Vector4>;
TYPED_TEST_CASE(VectorTests, MyTypes);


TYPED_TEST(VectorTests, Indexing)
{
    for (unsigned int i = 0; i < this->firstVector.GetDimensions(); i++)
    {
        this->firstVector[i] = VectorTests::VectorElementValues[0][i];
        EXPECT_EQ(this->firstVector[i], VectorTests::VectorElementValues[0][i]);
    }
}