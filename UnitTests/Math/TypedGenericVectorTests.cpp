#include "pch.h"

#include "Utility/Comparison/ComparisonUtility.h"
#include "Public/Game/Vector2.h"
#include "Public/Game/Vector3.h"
#include "Public/Game/Vector4.h"
#include "Public/Game/IntVector2.h"
#include "Public/Game/IntVector3.h"
#include "Public/Game/IntVector4.h"

namespace Maths::Vectors
{
    using namespace ArtemisEngine;

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