#include "pch.h"

#include "Engine/Math/Matrices/GenericMatrix.h"
#include "Engine/Math/Vectors/VectorBase.h"

namespace Math::Matrices
{
	using ArtemisEngine::Math::Matrices::BaseMatrix;
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

	const T DeterminantExpectedValue = -31.2343;

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

	const GenericMatrix<T, 1, 4> VectorMultiplicationExpectedResult(
	{
		VectorBase<T, 4>(2.25, 5.5, 26.5, 4.5),
	});

	const GenericMatrix<T, 4, 4> CofactorExpectedResult(
	{
		RowVector(-6.46875, -30.25, -40.6875, 24.15625),
		RowVector(8.984375, 14.25, 35.6875, -26.609375),
		RowVector(-2.109375, 1, 0.3125, -5.703125),
		RowVector(-2.265625, -22.0625, -45.9375, 26.265625),
	});

	const GenericMatrix<T, 4, 4> AdjoinedExpectedResult(
	{
		RowVector(-6.46875, 8.984375, -2.109375, -2.265625),
		RowVector(-30.25, 14.25, 1, -22.0625),
		RowVector(-40.6875, 35.6875, 0.3125, -45.9375),
		RowVector(24.15625, -26.609375, -5.703125, 26.265625),
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
	TEST(MatrixTest, Identity)
	{
		GenericMatrix<T, 4, 4> expectedResult(
		{
			RowVector(1, 0, 0, 0),
			RowVector(0, 1, 0, 0),
			RowVector(0, 0, 1, 0),
			RowVector(0, 0, 0, 1),
		});

		GenericMatrix<T, 4, 4> identityMatrix = BaseMatrix::GetIdentityMatrix<T, 4>();

		for (unsigned int i = 0; i < identityMatrix.GetRows(); i++)
		{
			for (unsigned int j = 0; j < identityMatrix.GetColumns(); j++)
			{
				EXPECT_EQ(expectedResult[i][j], identityMatrix[i][j]);
			}
		}
	}
	TEST(MatrixTest, MultiplicativeIdentity)
	{
		const RowVector* testValues = TestValues[0];

		Matrix a = GetTestMatrix(TestValues[0]);
		Matrix identity = BaseMatrix::GetIdentityMatrix<T, a.GetRows()>();

		Matrix b = a * identity;

		for (unsigned int i = 0; i < a.GetRows(); i++)
		{
			for (unsigned int j = 0; j < a.GetColumns(); j++)
			{
				EXPECT_EQ(a[i][j], b[i][j]);
			}
		}
	}
	TEST(MatrixTest, SquareMatrixCommunitativeIdentityMultiplication)
	{
		const RowVector* testValues = TestValues[0];

		Matrix a = GetTestMatrix(TestValues[0]);
		Matrix identity = BaseMatrix::GetIdentityMatrix<T, a.GetRows()>();

		Matrix b = a * identity;
		Matrix c = identity * a;

		for (unsigned int i = 0; i < a.GetRows(); i++)
		{
			for (unsigned int j = 0; j < a.GetColumns(); j++)
			{
				EXPECT_EQ(b[i][j], c[i][j]);
			}
		}
	}
	TEST(MatrixTest, SetRow)
	{
		VectorBase<T, 4> row(1, 2, 3, 4);

		GenericMatrix<T, 1, 4> matrix;
		matrix.SetRow(0, row);

		for (unsigned int i = 0; i < 4; i++)
		{
			EXPECT_EQ(matrix[0][i], row[i]);
		}
	}

	TEST(MatrixTest, SetColumn)
	{
		VectorBase<T, 4> column(1, 2, 3, 4);

		GenericMatrix<T, 4, 1> matrix;
		matrix.SetColumn(0, column);

		for (unsigned int i = 0; i < 4; i++)
		{
			EXPECT_EQ(matrix[i][0], column[i]);
		}
	}

	TEST(MatrixTest, AssignmentOperator)
	{
		const RowVector* testValues = TestValues[0];

		Matrix a = GetTestMatrix(testValues);
		Matrix b{};
		b = a;

		for (unsigned int i = 0; i < b.GetRows(); i++)
		{
			for (unsigned int j = 0; j < b.GetColumns(); j++)
			{
				EXPECT_EQ(testValues[i][j], a[i][j]);
				EXPECT_EQ(testValues[i][j], b[i][j]);
			}
		}
	}

	TEST(MatrixTest, MoveAssignmentOperator)
	{
		const RowVector* testValues = TestValues[0];

		Matrix a{};
		a = GetTestMatrix(testValues);

		for (unsigned int i = 0; i < a.GetRows(); i++)
		{
			for (unsigned int j = 0; j < a.GetColumns(); j++)
			{
				EXPECT_EQ(testValues[i][j], a[i][j]);
			}
		}
	}

	TEST(MatrixText, Equality)
	{
		Matrix a = GetTestMatrix(TestValues[0]);
		Matrix b = GetTestMatrix(TestValues[0]);
		Matrix c = GetTestMatrix(TestValues[1]);
		GenericMatrix<T, 1, 1> d{};
		
		EXPECT_EQ(true, a == b);
		EXPECT_EQ(false, a == c);
		EXPECT_EQ(false, a == d);
	}

	TEST(MatrixText, Inequality)
	{
		Matrix a = GetTestMatrix(TestValues[0]);
		Matrix b = GetTestMatrix(TestValues[0]);
		Matrix c = GetTestMatrix(TestValues[1]);
		GenericMatrix<T, 1, 1> d{};

		EXPECT_EQ(false, a != b);
		EXPECT_EQ(true, a != c);
		EXPECT_EQ(true, a != d);
	}

	TEST(MatrixTest, VectorMultiplication)
	{
		GenericMatrix<T, 2, 3> matrix(
		{
			VectorBase<T, 3>(6, 4, 3),
			VectorBase<T, 3>(0, 1, -2),
		});

		VectorBase<T, 3> vector(3, 0, -1.5);

		GenericMatrix<T, 2, 1> expectedResult{};
		expectedResult[0][0] = 13.5;
		expectedResult[1][0] = 3;

		GenericMatrix<T, 2, 1> result = matrix * vector;

		for (unsigned int i = 0; i < 2; i++)
		{
			EXPECT_EQ(expectedResult[0][i], result[0][i]);
		}
	}

	TEST(MatrixTest, Minor)
	{
		GenericMatrix<T, 4, 4> matrix(
		{
			VectorBase<T, 4>(2, -5, 3, 6),
			VectorBase<T, 4>(1, 0, 6, 2),
			VectorBase<T, 4>(-1, -2, 5, 7),
			VectorBase<T, 4>(1, 0, 3, 1),
		});

		unsigned int rowToDelete = 1;
		unsigned int columnToDelete = 0;

		GenericMatrix<T, 3, 3> expectedResult(
		{
			VectorBase<T, 3>(-5, 3, 6),
			VectorBase<T, 3>(-2, 5, 7),
			VectorBase<T, 3>(0, 3, 1),
		});

		GenericMatrix<T, 3, 3> minor = matrix.GetMinor(rowToDelete, columnToDelete);

		for (unsigned int i = 0; i < minor.GetRows(); i++)
		{
			for (unsigned int j = 0; j < minor.GetColumns(); j++)
			{
				EXPECT_EQ(expectedResult[i][j], minor[i][j]);
			}
		}
	}

	TEST(MatrixTest, Determinant)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		T expectedValue = DeterminantExpectedValue;

		T actualValue = matrix.GetDeterminant();

		EXPECT_NEAR(expectedValue, actualValue, 0.0001);
	}

	TEST(MatrixTest, CofactorMatrix)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix expectedValues = CofactorExpectedResult;

		Matrix actualValue = matrix.GetCofactorMatrix();

		for (unsigned int i = 0; i < actualValue.GetRows(); i++)
		{
			for (unsigned int j = 0; j < actualValue.GetColumns(); j++)
			{
				EXPECT_EQ(expectedValues[i][j], actualValue[i][j]);
			}
		}
	}

	TEST(MatrixTest, AdjointMatrix)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix expectedValues = AdjoinedExpectedResult;

		Matrix actualValue = matrix.GetAdjointMatrix();

		for (unsigned int i = 0; i < actualValue.GetRows(); i++)
		{
			for (unsigned int j = 0; j < actualValue.GetColumns(); j++)
			{
				EXPECT_EQ(expectedValues[i][j], actualValue[i][j]);
			}
		}
	}
}