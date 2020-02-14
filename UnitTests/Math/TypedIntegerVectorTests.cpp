#include "pch.h"

#include <map>
#include <list>

#include "Utility/Comparison/ComparisonUtility.h"
#include "Utility/Comparison/ComparisonUtilityVectors.h"
#include "Exceptions/DivideByZeroException.h"
#include "Engine/IntVector2.h"
#include "Engine/IntVector3.h"
#include "Engine/IntVector4.h"
#include "Engine/Vector2.h"
#include "Engine/Vector3.h"
#include "Engine/Vector4.h"

namespace Maths::Vectors
{
	using std::map;
	using std::list;

	using namespace ArtemisEngine;

	const int MaximumDimensions = 4;

	template<typename T>
	class TypedIntegerVectorTests : public ::testing::Test
	{
	};

	using MyTypes = ::testing::Types<IntVector2, IntVector3, IntVector4>;
    TYPED_TEST_CASE(TypedIntegerVectorTests, MyTypes);


	TYPED_TEST(TypedIntegerVectorTests, CopyConstructor)
	{
		TypeParam expectedResult({ 15, 5, 3, -1 });
		TypeParam copy({ 15, 5, 3, -1 });
		

		TypeParam actualResult(copy);
		

		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, Indexing)
	{
		int expectedResult[MaximumDimensions]{ 15, 5, 3, -1 };
		TypeParam actualResult({ 15, 5, 3, -1 });
				
		
		for (unsigned int i = 0; i < actualResult.GetDimensions(); i++)
			ExpectNear(expectedResult[i], actualResult[i]);
	}
	TYPED_TEST(TypedIntegerVectorTests, ConstIndexing)
	{
		int expectedResult[MaximumDimensions]{ 15, 5, 3, -1 };
		const TypeParam actualResult({ 15, 5, 3, -1 });


		for (unsigned int i = 0; i < actualResult.GetDimensions(); i++)
			ExpectNear(expectedResult[i], actualResult[i]);
	}
	TYPED_TEST(TypedIntegerVectorTests, GetDotProduct)
	{
		map<unsigned int, int> expectedValues
		{
			{ 2, 5 },
			{ 3, 8 },
			{ 4, 3 },
		};
		TypeParam a({ 15, 5, 3, -1 });
		TypeParam b({ 1, -2, 1, 5 });
		double expectedResult = expectedValues[a.GetDimensions()];
		
		
		double actualResult = TypeParam::GetDotProduct(a, b);
				
		
		ExpectEqual(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, GetAngle)
	{
		map<unsigned int, double> expectedValues
		{
			{ 2, 81.869897645844034 },
			{ 3, 78.291151727557974 },
			{ 4, 88.085050950218601 },
		};
		TypeParam a({ 15, 5, 3, -1 });
		TypeParam b({ 1, -2, 1, 5 });
		double expectedResult = expectedValues[a.GetDimensions()];
		

		double actualResult = TypeParam::GetAngle(a, b);


		ExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, SqrMagnitude)
	{
		map<unsigned int, double> expectedValues
		{
			{ 2, 250 },
			{ 3, 259 },
			{ 4, 260 },
		};
		TypeParam vector({ 15, 5, 3, -1 });
		int expectedResult = expectedValues[vector.GetDimensions()];


		int actualResult = vector.GetSqrMagnitude();


		ExpectEqual(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, Magnitude)
	{
		map<unsigned int, double> expectedValues
		{
			{ 2, 15.8113883008 },
			{ 3, 16.0934769394 },
			{ 4, 16.1245154966 },
		};
		TypeParam vector({ 15, 5, 3, -1 });
		double expectedResult = expectedValues[vector.GetDimensions()];


		double actualResult = vector.GetMagnitude();


		ExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, Normalized)
	{
		TypeParam vector({ 15, 5, 3, -1 });
		map<unsigned int, Vector4> expectedValues
		{
			{ 2, Vector2(0.94868329805051377, 0.31622776601683794) },
			{ 3, Vector3(0.93205464900180002, 0.31068488300060004, 0.18641092980036) },
			{ 4, Vector4(0.93026050941906346, 0.31008683647302115, 0.18605210188381269, -0.062017367294604234) },
		};
		Vector4 expectedResult = expectedValues[vector.GetDimensions()];


		Vector4 actualResult = vector.GetNormalized();


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, NormalizedZeroLengthException)
	{
		TypeParam vector{};


		ExpectThrow(vector.GetNormalized(), DivideByZeroException);
	}

	TYPED_TEST(TypedIntegerVectorTests, ToString)
	{
		map<unsigned int, string> expectedStrings
		{
			{ 2, "(15, 5)" },
			{ 3, "(15, 5, 3)" },
			{ 4, "(15, 5, 3, -1)" },
		};
		TypeParam vector({ 15, 5, 3, -1 });
		string expectedResult = expectedStrings[vector.GetDimensions()];


		string actualResult = vector.ToString();


		ExpectEqual(expectedResult, actualResult);
	}
	
	TYPED_TEST(TypedIntegerVectorTests, AdditionOfTwoVectors)
	{
		TypeParam expectedResult({ 16, 3, 4, 4 });
		TypeParam a({ 15, 5, 3, -1 });
		TypeParam b({ 1, -2, 1, 5 });
		TypeParam actualResult{ };


		actualResult = a + b;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, AdditionAssignment)
	{
		TypeParam expectedResult({ 16, 3, 4, 4 });
		TypeParam actualResult({ 15, 5, 3, -1 });
		TypeParam vector({ 1, -2, 1, 5 });

		
		actualResult += vector;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerScalarAddition)
	{
		TypeParam expectedResult({ 18, 8, 6, 2 });
		TypeParam vector({ 15, 5, 3, -1 });
		TypeParam actualResult;
		int scalar = 3;


		actualResult = vector + scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarAddition)
	{
		TypeParam expectedResult({ 19, 9, 7, 3 });
		TypeParam vector({ 15, 5, 3, -1 });
		TypeParam actualResult;
		double scalar = 4.35;
		

		actualResult = vector + scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerScalarAdditionAssignment)
	{
		TypeParam expectedResult({ 20, 10, 8, 4 });
		TypeParam actualResult({ 15, 5, 3, -1 });
		int scalar = 5;

		
		actualResult += scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarAdditionAssignment)
	{
		TypeParam expectedResult({ 25, 15, 13, 9 });
		TypeParam actualResult({ 20, 10, 8, 4 });
		double scalar = 5.86;
				

		actualResult += scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, SubtractionOfTwoVectors)
	{
		TypeParam expectedResult({ 14, 7, 2, -6 });
		TypeParam a({ 15, 5, 3, -1 });
		TypeParam b({ 1, -2, 1, 5 });
		TypeParam actualResult{ };


		actualResult = a - b;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, SubtractionAssignment)
	{
		TypeParam expectedResult({ 14, 7, 2, -6 });
		TypeParam actualResult({ 15, 5, 3, -1 });
		TypeParam vector({ 1, -2, 1, 5 });


		actualResult -= vector;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerPointScalarSubtraction)
	{
		TypeParam expectedResult({ 7, -3, -5, -9 });
		TypeParam vector({ 11, 1, -1, -5 });
		TypeParam actualResult;
		int scalar = 4;


		actualResult = vector - scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarSubtraction)
	{
		TypeParam expectedResult({ 6, -3, -5, -9 });
		TypeParam vector({ 11, 1, -1, -5 });
		TypeParam actualResult;
		double scalar = 4.68;
		

		actualResult = vector - scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerScalarSubtractionAssignment)
	{
		TypeParam expectedResult({ 7, -3, -5, -9 });
		TypeParam actualResult({ 11, 1, -1, -5 });
		int scalar = 4;


		actualResult -= scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarSubtractionAssignment)
	{
		TypeParam expectedResult({ 11, 1, 0, -4 });
		TypeParam actualResult({ 15, 5, 3, -1 });
		double scalar = 3.84;


		actualResult -= scalar;


		VectorExpectNear(expectedResult, actualResult);
	}
	
	TYPED_TEST(TypedIntegerVectorTests, IntegerPointScalarMultiplication)
	{
		TypeParam expectedResult({ 30, 10, 6, -2 });
		TypeParam vector({ 15, 5, 3, -1 });
		TypeParam actualResult;
		int scalar = 2;


		actualResult = vector * scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarMultiplication)
	{
		TypeParam expectedResult({ 37, 12, 7, -2 });
		TypeParam vector({ 15, 5, 3, -1 });
		TypeParam actualResult;
		double scalar = 2.5;


		actualResult = vector * scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerScalarMultiplicationAssignment)
	{
		TypeParam expectedResult({ 30, 10, 6, -2 });
		TypeParam actualResult({ 15, 5, 3, -1 });
		int scalar = 2;


		actualResult *= scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarMultiplicationAssignment)
	{
		TypeParam expectedResult({ 37, 12, 7, -2 });
		TypeParam actualResult({ 15, 5, 3, -1 });
		double scalar = 2.5;


		actualResult *= scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerScalarDivision)
	{
		TypeParam expectedResult({ 7, 2, 1, 0 });
		TypeParam vector({ 15, 5, 3, -1 });
		TypeParam actualResult;
		int scalar = 2;


		actualResult = vector / scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarDivision)
	{
		TypeParam expectedResult({ 6, 2, 1, 0 });
		TypeParam vector({ 15, 5, 3, -1 });
		TypeParam actualResult;
		double scalar = 2.5;


		actualResult = vector / scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerScalarDivisionAssignment)
	{
		TypeParam expectedResult({ 7, 2, 1, 0 });
		TypeParam actualResult({ 15, 5, 3, -1 });
		int scalar = 2;


		actualResult /= scalar;


		VectorExpectNear(expectedResult, actualResult);
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarDivisionAssignment)
	{
		TypeParam expectedResult({ 6, 2, 1, 0 });
		TypeParam actualResult({ 15, 5, 3, -1 });
		double scalar = 2.5;


		actualResult /= scalar;


		VectorExpectNear(expectedResult, actualResult);
	}
}