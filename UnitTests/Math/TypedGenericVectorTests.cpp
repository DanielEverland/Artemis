#include "pch.h"

#include "Engine/Vector2.h"
#include "Engine/Vector3.h"
#include "Engine/Vector4.h"
#include "Engine/IntVector2.h"
#include "Engine/IntVector3.h"
#include "Engine/IntVector4.h"

namespace Math::Vectors
{
    using ArtemisEngine::Vector2;
    using ArtemisEngine::Vector3;
    using ArtemisEngine::Vector4;
    using ArtemisEngine::IntVector2;
    using ArtemisEngine::IntVector3;
    using ArtemisEngine::IntVector4;

    template <typename T>
    class TypedGenericVectorTests : public ::testing::Test
    {
    public:
        const static int VectorsToInstantiate = 4;

        T vectors[VectorsToInstantiate];

        T CallConstructorNoArguments()
        {
            return T();
        }
    };

    using MyTypes = ::testing::Types<Vector2, Vector3, Vector4, IntVector2, IntVector3, IntVector4>;
    TYPED_TEST_CASE(TypedGenericVectorTests, MyTypes);

    TYPED_TEST(TypedGenericVectorTests, EmptyConstructor)
    {
        TypeParam vector = this->CallConstructorNoArguments();

        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
        {
            EXPECT_EQ(0, vector[i]);
        }
    }

    TYPED_TEST(TypedGenericVectorTests, DimensionIsPositive)
    {
        TypeParam vector = this->vectors[0];

        EXPECT_LT(0, vector.GetDimensions());
    }

    TYPED_TEST(TypedGenericVectorTests, IndexingOutOfRange)
    {
        TypeParam vector = this->vectors[0];

        EXPECT_THROW(vector[-1] = 0, OutOfRangeException);
        EXPECT_THROW(vector[100] = 0, OutOfRangeException);
    }

    TYPED_TEST(TypedGenericVectorTests, ConstIndexingOutOfRange)
    {
        TypeParam const vector = this->vectors[0];

        EXPECT_THROW(vector[-1], OutOfRangeException);
        EXPECT_THROW(vector[100], OutOfRangeException);
    }
}