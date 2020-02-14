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

	const double FloatingPointComparisonPrecision = 0.00001;

	template<typename T>
	class TypedIntegerVectorTests : public ::testing::Test
	{
	public:
		const static int VectorsToInstantiate = 4;
		const static int MaximumDimensions = 4;
		const static int SetCount = 5;

		const static int ElementValues[SetCount][MaximumDimensions];
		static map<unsigned int, list<double>> ExpectedNormalizedValues;
		static map<unsigned int, string> ExpectedStrings;
		static map<unsigned int, int> ExpectedDotProduct;
		static map<unsigned int, double> ExpectedAngle;
		static map<unsigned int, double> ExpectedMagnitude;

		T vectors[VectorsToInstantiate];

		double GetAngle(T a, T b)
		{
			return T::GetAngle(a, b);
		}
		int GetDotProduct(T a, T b)
		{
			return T::GetDotProduct(a, b);
		}
		void InitializeToDefaultValues(T& vector, const int* const elements) const
		{
			for (unsigned int i = 0; i < vector.GetDimensions(); i++)
			    vector[i] = elements[i];
		}
		T CallCopyConstructor(const T& copy)
		{
			return T(copy);
		}
	};

	using MyTypes = ::testing::Types<IntVector2, IntVector3, IntVector4>;
    TYPED_TEST_CASE(TypedIntegerVectorTests, MyTypes);

    template <typename T>
    const int TypedIntegerVectorTests<T>::ElementValues[SetCount][MaximumDimensions]
    {
        { 15, 5, 3, -1 },
        { 1, -2, 1, 5 },
        { -1, 0, -3, -1 },
        { 3, 2, -5, 3 },
        { -1, 0, 3, 3 },
    };
	
	template<typename T>
	map<unsigned int, double> TypedIntegerVectorTests<T>::ExpectedMagnitude
	{
		{ 2, 15.81139 },
		{ 3, 16.09348 },
		{ 4, 16.12452 },
	};

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
			TempExpectNear(expectedResult[i], actualResult[i]);
	}
	TYPED_TEST(TypedIntegerVectorTests, ConstIndexing)
	{
		int expectedResult[MaximumDimensions]{ 15, 5, 3, -1 };
		const TypeParam actualResult({ 15, 5, 3, -1 });


		for (unsigned int i = 0; i < actualResult.GetDimensions(); i++)
			TempExpectNear(expectedResult[i], actualResult[i]);
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
				
		
		TempExpectEqual(expectedResult, actualResult);
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


		TempExpectNear(expectedResult, actualResult);
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


		TempExpectEqual(expectedResult, actualResult);
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


		TempExpectNear(expectedResult, actualResult);
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


		TempExpectEqual(expectedResult, actualResult);
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
		TypeParam vector = this->vectors[0];
		int scalar = 2;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[0];

		this->InitializeToDefaultValues(vector, ElementValues);


		vector *= scalar;


		for (unsigned int i = 0; i < vector.GetDimensions(); i++)
		{
			EXPECT_EQ(ElementValues[i] * scalar, vector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarMultiplicationAssignment)
	{
		TypeParam vector = this->vectors[0];
		double scalar = -1.432;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[0];

		this->InitializeToDefaultValues(vector, ElementValues);


		vector *= scalar;


		for (unsigned int i = 0; i < vector.GetDimensions(); i++)
		{
			EXPECT_EQ(static_cast<long>(ElementValues[i] * scalar), vector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, DivisionOfTwoVectors)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];
		TypeParam cVector = this->vectors[2];

		const int* aElementValues = TypedIntegerVectorTests::ElementValues[0];
		const int* bElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(aVector, aElementValues);
		this->InitializeToDefaultValues(bVector, bElementValues);


		cVector = aVector / bVector;


		for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
		{
			EXPECT_EQ(aElementValues[i] / bElementValues[i], cVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, DivisionAssignment)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];

		const int* aElementValues = TypedIntegerVectorTests::ElementValues[0];
		const int* bElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(aVector, aElementValues);
		this->InitializeToDefaultValues(bVector, bElementValues);


		aVector /= bVector;


		for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
		{
			EXPECT_EQ(aElementValues[i] / bElementValues[i], aVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerScalarDivision)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];
		int scalar = 34;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(bVector, ElementValues);


		aVector = bVector / scalar;


		for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
		{
			EXPECT_EQ(bVector[i] / scalar, aVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarDivision)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];
		double scalar = 2.54;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(bVector, ElementValues);


		aVector = bVector / scalar;


		for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
		{
			EXPECT_EQ(static_cast<long>(bVector[i] / scalar), aVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerScalarDivisionAssignment)
	{
		TypeParam vector = this->vectors[0];
		int scalar = 4;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[0];

		this->InitializeToDefaultValues(vector, ElementValues);


		vector /= scalar;


		for (unsigned int i = 0; i < vector.GetDimensions(); i++)
		{
			EXPECT_EQ(ElementValues[i] / scalar, vector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarDivisionAssignment)
	{
		TypeParam vector = this->vectors[0];
		double scalar = 4.21;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[0];

		this->InitializeToDefaultValues(vector, ElementValues);


		vector /= scalar;


		for (unsigned int i = 0; i < vector.GetDimensions(); i++)
		{
			EXPECT_EQ(static_cast<long>(ElementValues[i] / scalar), vector[i]);
		}
	}
}