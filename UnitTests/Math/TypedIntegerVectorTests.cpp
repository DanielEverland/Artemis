#include "pch.h"

#include <map>
#include <list>

#include "Utility/Comparison/ComparisonUtility.h"
#include "Utility/Comparison/ComparisonUtilityVectors.h"
#include "Exceptions/DivideByZeroException.h"
#include "Engine/IntVector2.h"
#include "Engine/IntVector3.h"
#include "Engine/IntVector4.h"

namespace Maths::Vectors
{
	using std::map;
	using std::list;

	using ArtemisEngine::IntVector2;
	using ArtemisEngine::IntVector3;
	using ArtemisEngine::IntVector4;

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
	
	template <typename T>
	map<unsigned int, list<double>> TypedIntegerVectorTests<T>::ExpectedNormalizedValues
	{
		{ 2, list<double> { 0.94868, 0.31623 } },
		{ 3, list<double> { 0.93205, 0.31068, 0.18641 } },
		{ 4, list<double> { 0.93026, 0.31009, 0.18605, -0.06202 } },
	};

	template<typename T>
	map<unsigned int, string> TypedIntegerVectorTests<T>::ExpectedStrings
	{
		{ 2, "(15, 5)" },
		{ 3, "(15, 5, 3)" },
		{ 4, "(15, 5, 3, -1)" },
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
		double expectedResult = expectedValues[vector.GetDimensions()];


		double actualResult = vector.GetSqrMagnitude();


		TempExpectNear(expectedResult, actualResult);
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
		TypeParam vector = this->vectors[0];
		list<double> expectedValues = TypedIntegerVectorTests::ExpectedNormalizedValues[vector.GetDimensions()];
		const int* elementValues = TypedIntegerVectorTests::ElementValues[0];

		TypedIntegerVectorTests::InitializeToDefaultValues(vector, elementValues);


		auto normalized = vector.GetNormalized();


		for (unsigned int i = 0; i < vector.GetDimensions(); i++)
		{
			auto iter = expectedValues.begin();
			std::advance(iter, i);

			EXPECT_NEAR(*iter, normalized[i], FloatingPointComparisonPrecision);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, NormalizedZeroLengthException)
	{
		TypeParam vector = this->vectors[0];

		EXPECT_THROW(vector.GetNormalized(), DivideByZeroException);
	}

	TYPED_TEST(TypedIntegerVectorTests, ToString)
	{
		TypeParam vector = this->vectors[0];
		string expectedString = TypedIntegerVectorTests::ExpectedStrings[vector.GetDimensions()];
		const int* elementValues = TypedIntegerVectorTests::ElementValues[0];

		this->InitializeToDefaultValues(vector, elementValues);


		string vectorString = vector.ToString();


		EXPECT_EQ(expectedString, vectorString);
	}
	
	TYPED_TEST(TypedIntegerVectorTests, AdditionOfTwoVectors)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];
		TypeParam cVector = this->vectors[2];

		const int* aElementValues = TypedIntegerVectorTests::ElementValues[0];
		const int* bElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(aVector, aElementValues);
		this->InitializeToDefaultValues(bVector, bElementValues);


		cVector = aVector + bVector;


		for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
		{
			EXPECT_EQ(aElementValues[i] + bElementValues[i], cVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, AdditionAssignment)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];

		const int* aElementValues = TypedIntegerVectorTests::ElementValues[0];
		const int* bElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(aVector, aElementValues);
		this->InitializeToDefaultValues(bVector, bElementValues);


		aVector += bVector;


		for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
		{
			EXPECT_EQ(aElementValues[i] + bElementValues[i], aVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerScalarAddition)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];
		int scalar = 3;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(bVector, ElementValues);


		aVector = bVector + scalar;


		for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
		{
			EXPECT_EQ(bVector[i] + scalar, aVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarAddition)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];
		double scalar = 4.35;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(bVector, ElementValues);


		aVector = bVector + scalar;


		for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
		{
			EXPECT_EQ(static_cast<long>(bVector[i] + scalar), aVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerScalarAdditionAssignment)
	{
		TypeParam vector = this->vectors[0];
		int scalar = 5;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[0];

		this->InitializeToDefaultValues(vector, ElementValues);


		vector += scalar;


		for (unsigned int i = 0; i < vector.GetDimensions(); i++)
		{
			EXPECT_EQ(ElementValues[i] + scalar, vector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarAdditionAssignment)
	{
		TypeParam vector = this->vectors[0];
		double scalar = 5.86;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[0];

		this->InitializeToDefaultValues(vector, ElementValues);


		vector += scalar;


		for (unsigned int i = 0; i < vector.GetDimensions(); i++)
		{
			EXPECT_EQ(static_cast<long>(ElementValues[i] + scalar), vector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, SubtractionOfTwoVectors)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];
		TypeParam cVector = this->vectors[2];

		const int* aElementValues = TypedIntegerVectorTests::ElementValues[0];
		const int* bElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(aVector, aElementValues);
		this->InitializeToDefaultValues(bVector, bElementValues);


		cVector = aVector - bVector;


		for (unsigned int i = 0; i < cVector.GetDimensions(); i++)
		{
			EXPECT_EQ(aElementValues[i] - bElementValues[i], cVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, SubtractionAssignment)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];

		const int* aElementValues = TypedIntegerVectorTests::ElementValues[0];
		const int* bElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(aVector, aElementValues);
		this->InitializeToDefaultValues(bVector, bElementValues);


		aVector -= bVector;


		for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
		{
			EXPECT_EQ(aElementValues[i] - bElementValues[i], aVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerPointScalarSubtraction)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];
		int scalar = 54;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(bVector, ElementValues);


		aVector = bVector - scalar;


		for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
		{
			EXPECT_EQ(bVector[i] - scalar, aVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarSubtraction)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];
		double scalar = 5.68;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(bVector, ElementValues);


		aVector = bVector - scalar;


		for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
		{
			EXPECT_EQ(static_cast<long>(bVector[i] - scalar), aVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, IntegerScalarSubtractionAssignment)
	{
		TypeParam vector = this->vectors[0];
		int scalar = 7;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[0];

		this->InitializeToDefaultValues(vector, ElementValues);


		vector -= scalar;


		for (unsigned int i = 0; i < vector.GetDimensions(); i++)
		{
			EXPECT_EQ(ElementValues[i] - scalar, vector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarSubtractionAssignment)
	{
		TypeParam vector = this->vectors[0];
		double scalar = 7.84;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[0];

		this->InitializeToDefaultValues(vector, ElementValues);


		vector -= scalar;


		for (unsigned int i = 0; i < vector.GetDimensions(); i++)
		{
			EXPECT_EQ(static_cast<long>(ElementValues[i] - scalar), vector[i]);
		}
	}
	
	TYPED_TEST(TypedIntegerVectorTests, IntegerPointScalarMultiplication)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];
		int scalar = 15;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(bVector, ElementValues);


		aVector = bVector * scalar;


		for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
		{
			EXPECT_EQ(bVector[i] * scalar, aVector[i]);
		}
	}

	TYPED_TEST(TypedIntegerVectorTests, FloatingPointScalarMultiplication)
	{
		TypeParam aVector = this->vectors[0];
		TypeParam bVector = this->vectors[1];
		double scalar = 6.154;

		const int* ElementValues = TypedIntegerVectorTests::ElementValues[1];

		this->InitializeToDefaultValues(bVector, ElementValues);


		aVector = bVector * scalar;


		for (unsigned int i = 0; i < aVector.GetDimensions(); i++)
		{
			EXPECT_EQ(static_cast<long>(bVector[i] * scalar), aVector[i]);
		}
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