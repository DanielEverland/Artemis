#include "pch.h"

#include "Utility/Comparison/ComparisonUtility.h"
#include "Engine/Vector2.h"
#include "Engine/Vector3.h"
#include "Engine/Vector4.h"
#include "Engine/IntVector2.h"
#include "Engine/IntVector3.h"
#include "Engine/IntVector4.h"

namespace Maths::Vectors
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
    };

    using MyTypes = ::testing::Types<Vector2, Vector3, Vector4, IntVector2, IntVector3, IntVector4>;
    TYPED_TEST_CASE(TypedGenericVectorTests, MyTypes);

    TYPED_TEST(TypedGenericVectorTests, EmptyConstructor)
    {
        TypeParam vector{ };


        for (unsigned int i = 0; i < vector.GetDimensions(); i++)
            ExpectZero(vector[i]);
    }
    
    TYPED_TEST(TypedGenericVectorTests, IndexingOutOfRange)
    {
        TypeParam vector{ };


        ExpectThrow(vector[-1] = 0, OutOfRangeException);
        ExpectThrow(vector[100] = 0, OutOfRangeException);
    }

    TYPED_TEST(TypedGenericVectorTests, ConstIndexingOutOfRange)
    {
        const TypeParam vector{ };


        ExpectThrow(vector[-1], OutOfRangeException);
        ExpectThrow(vector[100], OutOfRangeException);
    }
}