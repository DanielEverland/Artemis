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

	typedef VectorBase<T, columns> RowVector;
	typedef VectorBase<T, columns> ColumnVector;
	typedef GenericMatrix<T, rows, columns> Matrix;
	typedef	GenericMatrix<T, 1, columns> RowMatrix;
	typedef	GenericMatrix<T, rows, 1> ColumnMatrix;
	
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

	const GenericMatrix<T, 4, 4> InverseExpectedResult(
	{
		RowVector(0.20710, -0.28764, 0.06753, 0.07253),
		RowVector(0.96848, -0.45622, -0.03201, 0.70635),
		RowVector(1.30265, -1.14257, -0.01000, 1.47073),
		RowVector(-0.77338, 0.85192, 0.18259, -0.84092),
	});

	const GenericMatrix<T, 4, 4> IdentityExpectedResult
	({
		RowVector(1, 0, 0, 0),
		RowVector(0, 1, 0, 0),
		RowVector(0, 0, 1, 0),
		RowVector(0, 0, 0, 1),
	});

	Matrix GetTestMatrix(const RowVector* rowVectorArray)
	{
		return Matrix({ rowVectorArray[0], rowVectorArray[1], rowVectorArray[2], rowVectorArray[3] });
	}

	Matrix IterateWorkOnMatrices(const Matrix& a, const Matrix& b, T (*action)(T a, T b))
	{
		Matrix output;

		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				output[i][j] += action(a[i][j], b[i][j]);
			}
		}

		return output;
	}
	Matrix IterateWorkOnMatrices(const Matrix& a, T b, T(*action)(T a, T b))
	{
		Matrix output;

		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				output[i][j] += action(a[i][j], b);
			}
		}

		return output;
	}
	Matrix Add(const Matrix& a, const Matrix& b)
	{
		return IterateWorkOnMatrices(a, b, [](T a, T b) -> T
			{
				return a + b;
			});
	}
	Matrix Subtract(const Matrix& a, const Matrix& b)
	{
		return IterateWorkOnMatrices(a, b, [](T a, T b) -> T
			{
				return a - b;
			});
	}
	Matrix Divide(const Matrix& a, const Matrix& b)
	{
		return IterateWorkOnMatrices(a, b, [](T a, T b) -> T
			{
				return a / b;
			});
	}
	Matrix Multiply(const Matrix& a, const Matrix& b)
	{
		return IterateWorkOnMatrices(a, b, [](T a, T b) -> T
			{
				return a * b;
			});
	}
	Matrix MultiplyScalar(const Matrix& a, T scalar)
	{
		return IterateWorkOnMatrices(a, scalar, [](T a, T b) -> T
			{
				return a * b;
			});
	}

	void ExpectEmpty(Matrix actualValues)
	{
		for (unsigned int i = 0; i < actualValues.GetRows(); i++)
		{
			for (unsigned j = 0; j < actualValues.GetColumns(); j++)
			{
				EXPECT_EQ(0, actualValues[i][j]);
			}
		}
	}
	void ExpectEqual(const RowVector* expectedValues, const Matrix actualValues)
	{
		for (unsigned int i = 0; i < actualValues.GetRows(); i++)
		{
			for (unsigned int j = 0; j < actualValues.GetColumns(); j++)
			{
				EXPECT_EQ(expectedValues[i][j], actualValues[i][j]);
			}
		}
	}
	void ExpectEqual(const Matrix expectedValues, const Matrix actualValues)
	{
		for (unsigned int i = 0; i < actualValues.GetRows(); i++)
		{
			for (unsigned int j = 0; j < actualValues.GetColumns(); j++)
			{
				EXPECT_EQ(expectedValues[i][j], actualValues[i][j]);
			}
		}
	}
	template<class T, unsigned int rows, unsigned int columns>
	void ExpectRowEqual(const GenericMatrix<T, rows, columns> expectedValues, const VectorBase<T, columns>& row, int rowIndex = 0)
	{
		for (unsigned int i = 0; i < row.GetDimensions(); i++)
		{
			EXPECT_EQ(expectedValues[0][i], row[i]);
		}
	}
	template<class T, unsigned int rows, unsigned int columns>
	void ExpectColumnEqual(const GenericMatrix<T, rows, columns> expectedValues, const VectorBase<T, rows>& column, int columnIndex = 0)
	{
		for (unsigned int i = 0; i < column.GetDimensions(); i++)
		{
			EXPECT_EQ(expectedValues[i][0], column[i]);
		}
	}

	TEST(MatrixTest, EmptyConstructor)
	{
		Matrix matrix;


		ExpectEmpty(matrix);
	}
	TEST(MatrixTest, InitializerListConstructor)
	{
		const RowVector* expectedValues = TestValues[0];


		Matrix matrix({ expectedValues[0], expectedValues[1], expectedValues[2], expectedValues[3] });


		ExpectEqual(expectedValues, matrix);
	}
	TEST(MatrixTest, MultiDimensionalIndexer)
	{
		const RowVector* expectedValues = TestValues[0];


		Matrix matrix = GetTestMatrix(expectedValues);


		ExpectEqual(expectedValues, matrix);
	}
	TEST(MatrixTest, Addition)
	{
		Matrix a = GetTestMatrix(TestValues[0]);
		Matrix b = GetTestMatrix(TestValues[1]);
		Matrix expectedValues = Add(a, b);


		Matrix actualValues = a + b;


		ExpectEqual(expectedValues, actualValues);
	}
	TEST(MatrixTest, AdditionAssignment)
	{
		Matrix actualValues = GetTestMatrix(TestValues[0]);
		Matrix b = GetTestMatrix(TestValues[1]);
		Matrix expectedValues = Add(actualValues, b);


		actualValues += b;


		ExpectEqual(expectedValues, actualValues);
	}
	TEST(MatrixTest, Subtraction)
	{
		Matrix a = GetTestMatrix(TestValues[0]);
		Matrix b = GetTestMatrix(TestValues[1]);
		Matrix expectedValues = Subtract(a, b);
		

		Matrix actualValues = a - b;


		ExpectEqual(expectedValues, actualValues);
	}
	TEST(MatrixTest, SubtractionAssignment)
	{
		Matrix actualValues = GetTestMatrix(TestValues[0]);
		Matrix b = GetTestMatrix(TestValues[1]);
		Matrix expectedValues = Subtract(actualValues, b);


		actualValues -= b;


		ExpectEqual(expectedValues, actualValues);
	}
	TEST(MatrixTest, ScalarMultiplication)
	{
		double scalar = 2;
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix expectedValues = MultiplyScalar(matrix, scalar);


		Matrix actualValues = matrix * scalar;


		ExpectEqual(expectedValues, actualValues);
	}
	TEST(MatrixTest, ScalarMultiplicationAssignment)
	{
		double scalar = 2;
		Matrix matrixValues = GetTestMatrix(TestValues[0]);
		Matrix expectedValues = MultiplyScalar(matrixValues, scalar);


		Matrix actualValues(matrixValues);
		actualValues *= scalar;


		ExpectEqual(expectedValues, actualValues);
	}
	TEST(MatrixTest, MatrixMultiplication)
	{
		GenericMatrix<T, 4, 2> matrixA = MatrixMultiplicationInputA;
		GenericMatrix<T, 2, 4> matrixB = MatrixMultiplicationInputB;
		GenericMatrix<T, 4, 4> expectedResult = MatrixMultiplicationExpectedResult;


		GenericMatrix<T, 4, 4> actualResult = matrixA * matrixB;


		ExpectEqual(expectedResult, actualResult);
	}
	TEST(MatrixTest, Transpose)
	{
		Matrix expectedResults = TransposeExpectedResult;
		Matrix matrix = GetTestMatrix(TestValues[0]);


		Matrix actualResults = matrix.GetTranspose();


		ExpectEqual(expectedResults, actualResults);
	}
	TEST(MatrixTest, Identity)
	{
		Matrix expectedResult = IdentityExpectedResult;


		Matrix actualResult = BaseMatrix::GetIdentityMatrix<T, 4>();


		ExpectEqual(expectedResult, actualResult);
	}
	TEST(MatrixTest, MultiplicativeIdentity)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix identity = matrix.GetIdentityMatrix();
		Matrix expectedResult(matrix);


		Matrix actualResult = matrix * identity;


		ExpectEqual(expectedResult, actualResult);
	}
	TEST(MatrixTest, SquareMatrixCommunitativeIdentityMultiplication)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix identity = matrix.GetIdentityMatrix();


		Matrix a = matrix * identity;
		Matrix b = identity * matrix;


		ExpectEqual(a, b);
	}
	TEST(MatrixTest, SetRow)
	{
		RowVector row(1, 2, 3, 4);
		RowMatrix matrix;


		matrix.SetRow(0, row);


		ExpectRowEqual(matrix, row);
	}

	TEST(MatrixTest, SetColumn)
	{
		ColumnVector column(1, 2, 3, 4);
		ColumnMatrix matrix;


		matrix.SetColumn(0, column);


		ExpectColumnEqual(matrix, column);
	}

	TEST(MatrixTest, AssignmentOperator)
	{
		Matrix a = GetTestMatrix(TestValues[0]);
		Matrix b{};


		b = a;


		ExpectEqual(a, b);
	}

	TEST(MatrixTest, MoveAssignmentOperator)
	{
		const RowVector* expectedValues = TestValues[0];


		Matrix actualValues = GetTestMatrix(expectedValues);


		ExpectEqual(expectedValues, actualValues);
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

		VectorBase<T, 2> expectedResult(13.5, 3);
		VectorBase<T, 2> actualResult = matrix * vector;

		for (unsigned int i = 0; i < 2; i++)
		{
			EXPECT_EQ(expectedResult[i], actualResult[i]);
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

	TEST(MatrixTest, Inverse)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix expectedValues = InverseExpectedResult;

		Matrix actualValue = matrix.GetInverseMatrix();

		for (unsigned int i = 0; i < actualValue.GetRows(); i++)
		{
			for (unsigned int j = 0; j < actualValue.GetColumns(); j++)
			{
				EXPECT_NEAR(expectedValues[i][j], actualValue[i][j], 0.0001);
			}
		}
	}
	TEST(MatrixTest, MultiplyingInverseMatrixReturnsIdentity)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix inverse = matrix.GetInverseMatrix();
		Matrix identity = matrix.GetIdentityMatrix();

		Matrix product = matrix * inverse;

		for (unsigned int i = 0; i < product.GetRows(); i++)
		{
			for (unsigned int j = 0; j < product.GetColumns(); j++)
			{
				EXPECT_NEAR(identity[i][j], product[i][j], 0.000001);
			}
		}
	}
	TEST(MatrixTest, InverseCommunatitiveMultiplication)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix inverse = matrix.GetInverseMatrix();

		Matrix a = matrix * inverse;
		Matrix b = inverse * matrix;

		for (unsigned int i = 0; i < a.GetRows(); i++)
		{
			for (unsigned int j = 0; j < a.GetColumns(); j++)
			{
				EXPECT_NEAR(a[i][j], b[i][j], 0.000001);
			}
		}
	}
	TEST(MatrixTest, ScaleTransform)
	{

	}
}