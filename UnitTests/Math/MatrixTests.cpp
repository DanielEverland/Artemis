#include "pch.h"

#include "Engine/Math/Matrices/GenericMatrix.h"
#include "Engine/Math/Vectors/VectorBase.h"

namespace Math::Matrices
{
	using ArtemisEngine::Math::Matrices::GenericMatrix;
	using ArtemisEngine::Math::Vectors::VectorBase;

	typedef double T;
	const unsigned int rows = 4;
	const unsigned int columns = 4;

	typedef GenericMatrix<T, rows, columns> Matrix;
	typedef VectorBase<T, columns> RowVector;

	const static RowVector TestValues[2][rows]
	{
		{
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		},
		{
			RowVector(4.25, -1.25, 3.0, 5.25),
			RowVector(-1.0, 1.25, 2.0, 3.25),
			RowVector(-0.75, -1.25, -2.0, 3.25),
			RowVector(2.50, -1.50, -1.75, 2.0),
		}
	};

	const GenericMatrix<T, 4, 2> MatrixMultiplicationInputA(
	{
		VectorBase<T, 2>(1, 2),
		VectorBase<T, 2>(4, -2),
		VectorBase<T, 2>(-5, 6),
		VectorBase<T, 2>(0, 2),
	});

	const GenericMatrix<T, 2, 4> MatrixMultiplicationInputB(
	{
		VectorBase<T, 4>(1, 2, 3, 4),
		VectorBase<T, 4>(-5, 5, 3, -2),
	});

	const GenericMatrix<T, 4, 4> MatrixMultiplicationExpectedResult(
	{
		VectorBase<T, 4>(-9, 12, 9, 0),
		VectorBase<T, 4>(14, -2, 6, 20),
		VectorBase<T, 4>(-35, 20, 3, -32),
		VectorBase<T, 4>(-10, 10, 6, -4),
	});

	const GenericMatrix<T, 4, 4> TransposeExpectedResult(
	{
		VectorBase<T, 4>(1.0, -2.75, 3.25, -3.0),
		VectorBase<T, 4>(2.50, 1.25, -1.0, -1.25),
		VectorBase<T, 4>(-1.25, 0.25, 2.75, 2.0),
		VectorBase<T, 4>(0.0, 1.25, 4.25, 1.0),
	});

	Matrix GetTestMatrix(const RowVector* rowVectorArray)
	{
		return Matrix({ rowVectorArray[0], rowVectorArray[1], rowVectorArray[2], rowVectorArray[3] });
	}

	TEST(MatrixTest, EmptyConstructor)
	{
		Matrix matrix;

		for (unsigned int i = 0; i < matrix.GetRows(); i++)
		{
			for (unsigned j = 0; j < matrix.GetColumns(); j++)
			{
				EXPECT_EQ(0, matrix.GetValue(i, j));
			}
		}
	}
	TEST(MatrixTest, InitializerListConstructor)
	{
		const RowVector* UsedTestValues = TestValues[0];

		Matrix matrix({ UsedTestValues[0], UsedTestValues[1], UsedTestValues[2], UsedTestValues[3] });

		for (unsigned int i = 0; i < matrix.GetRows(); i++)
		{
			for (unsigned int j = 0; j < matrix.GetColumns(); j++)
			{
				EXPECT_EQ(UsedTestValues[i][j], matrix.GetValue(i, j));
			}
		}
	}
	TEST(MatrixTest, MultiDimensionalIndexer)
	{
		const RowVector* testValuesRowVector = TestValues[0];
		Matrix matrix = GetTestMatrix(testValuesRowVector);

		for (unsigned int i = 0; i < matrix.GetRows(); i++)
		{
			for (unsigned int j = 0; j < matrix.GetColumns(); j++)
			{
				EXPECT_EQ(testValuesRowVector[i][j], matrix[i][j]);
			}
		}
	}
	TEST(MatrixTest, Addition)
	{
		const RowVector* aTestValues = TestValues[0];
		const RowVector* bTestValues = TestValues[1];

		Matrix a = GetTestMatrix(aTestValues);
		Matrix b = GetTestMatrix(bTestValues);

		Matrix c = a + b;

		for (unsigned int i = 0; i < c.GetRows(); i++)
		{
			for (unsigned int j = 0; j < c.GetColumns(); j++)
			{
				EXPECT_EQ(aTestValues[i][j] + bTestValues[i][j], c[i][j]);
			}
		}
	}
	TEST(MatrixTest, AdditionAssignment)
	{
		const RowVector* aTestValues = TestValues[0];
		const RowVector* bTestValues = TestValues[1];

		Matrix a = GetTestMatrix(aTestValues);
		Matrix b = GetTestMatrix(bTestValues);

		a += b;

		for (unsigned int i = 0; i < a.GetRows(); i++)
		{
			for (unsigned int j = 0; j < a.GetColumns(); j++)
			{
				EXPECT_EQ(aTestValues[i][j] + bTestValues[i][j], a[i][j]);
			}
		}
	}
	TEST(MatrixTest, Subtraction)
	{
		const RowVector* aTestValues = TestValues[0];
		const RowVector* bTestValues = TestValues[1];

		Matrix a = GetTestMatrix(aTestValues);
		Matrix b = GetTestMatrix(bTestValues);

		Matrix c = a - b;

		for (unsigned int i = 0; i < c.GetRows(); i++)
		{
			for (unsigned int j = 0; j < c.GetColumns(); j++)
			{
				EXPECT_EQ(aTestValues[i][j] - bTestValues[i][j], c[i][j]);
			}
		}
	}
	TEST(MatrixTest, SubtractionAssignment)
	{
		const RowVector* aTestValues = TestValues[0];
		const RowVector* bTestValues = TestValues[1];

		Matrix a = GetTestMatrix(aTestValues);
		Matrix b = GetTestMatrix(bTestValues);

		a -= b;

		for (unsigned int i = 0; i < a.GetRows(); i++)
		{
			for (unsigned int j = 0; j < a.GetColumns(); j++)
			{
				EXPECT_EQ(aTestValues[i][j] - bTestValues[i][j], a[i][j]);
			}
		}
	}
	TEST(MatrixTest, ScalarMultiplication)
	{
		const RowVector* aTestValues = TestValues[0];

		double scalar = 2;
		Matrix a = GetTestMatrix(aTestValues);

		Matrix b = a * scalar;

		for (unsigned int i = 0; i < b.GetRows(); i++)
		{
			for (unsigned int j = 0; j < b.GetColumns(); j++)
			{
				EXPECT_EQ(aTestValues[i][j] * scalar, b[i][j]);
				EXPECT_EQ(aTestValues[i][j], a[i][j]);
			}
		}
	}
	TEST(MatrixTest, ScalarMultiplicationAssignment)
	{
		const RowVector* aTestValues = TestValues[0];

		Matrix matrix = GetTestMatrix(aTestValues);
		double scalar = 2;

		matrix *= scalar;

		for (unsigned int i = 0; i < matrix.GetRows(); i++)
		{
			for (unsigned int j = 0; j < matrix.GetColumns(); j++)
			{
				EXPECT_EQ(aTestValues[i][j] * scalar, matrix[i][j]);
			}
		}
	}
	TEST(MatrixTest, MatrixMultiplication)
	{
		GenericMatrix<T, 4, 2> matrixA = MatrixMultiplicationInputA;
		GenericMatrix<T, 2, 4> matrixB = MatrixMultiplicationInputB;
		GenericMatrix<T, 4, 4> expectedResult = MatrixMultiplicationExpectedResult;

		GenericMatrix<T, 4, 4> actualResult = matrixA * matrixB;

		for (unsigned int i = 0; i < actualResult.GetRows(); i++)
		{
			for (unsigned int j = 0; j < actualResult.GetColumns(); j++)
			{
				EXPECT_EQ(expectedResult[i][j], actualResult[i][j]);
			}
		}
	}
	TEST(MatrixTest, Transpose)
	{
		const RowVector* testValues = TestValues[0];

		Matrix expectedResult = TransposeExpectedResult;
		Matrix matrix = GetTestMatrix(testValues);
		Matrix transpose = matrix.GetTranspose();

		for (unsigned int i = 0; i < transpose.GetRows(); i++)
		{
			for (unsigned int j = 0; j < transpose.GetColumns(); j++)
			{
				EXPECT_EQ(expectedResult[i][j], transpose[i][j]);
			}
		}
	}
}