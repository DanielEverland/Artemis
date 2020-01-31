#include "pch.h"

#include "Engine/Math/Matrices/GenericMatrix.h"
#include "Engine/Math/Vectors/VectorBase.h"
#include "Utility/Comparison/ComparisonUtility.h"
#include "Utility/Comparison/ComparisonUtilityMatrix.h"

namespace Math::Matrices
{
	using namespace ArtemisEngine::UnitTests::Comparisons;
	using ArtemisEngine::Math::Matrices::BaseMatrix;
	using ArtemisEngine::Math::Matrices::GenericMatrix;
	using ArtemisEngine::Math::Vectors::VectorBase;

	const unsigned int rows = 4;
	const unsigned int columns = 4;
	const double nearComparisonPrecision = 1e-8;

	typedef VectorBase<double, columns> RowVector;
	typedef VectorBase<double, columns> ColumnVector;
	typedef GenericMatrix<double, rows, columns> Matrix;
	typedef	GenericMatrix<double, 1, columns> RowMatrix;
	typedef	GenericMatrix<double, rows, 1> ColumnMatrix;
	
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

	const double DeterminantExpectedValue = -31.2343;

	const GenericMatrix<double, 4, 2> MatrixMultiplicationInputA(
	{
		VectorBase<double, 2>(1, 2),
		VectorBase<double, 2>(4, -2),
		VectorBase<double, 2>(-5, 6),
		VectorBase<double, 2>(0, 2),
	});

	const GenericMatrix<double, 2, 4> MatrixMultiplicationInputB(
	{
		VectorBase<double, 4>(1, 2, 3, 4),
		VectorBase<double, 4>(-5, 5, 3, -2),
	});

	const GenericMatrix<double, 4, 4> MatrixMultiplicationExpectedResult(
	{
		VectorBase<double, 4>(-9, 12, 9, 0),
		VectorBase<double, 4>(14, -2, 6, 20),
		VectorBase<double, 4>(-35, 20, 3, -32),
		VectorBase<double, 4>(-10, 10, 6, -4),
	});

	const GenericMatrix<double, 4, 4> TransposeExpectedResult(
	{
		VectorBase<double, 4>(1.0, -2.75, 3.25, -3.0),
		VectorBase<double, 4>(2.50, 1.25, -1.0, -1.25),
		VectorBase<double, 4>(-1.25, 0.25, 2.75, 2.0),
		VectorBase<double, 4>(0.0, 1.25, 4.25, 1.0),
	});

	const GenericMatrix<double, 1, 4> VectorMultiplicationExpectedResult(
	{
		VectorBase<double, 4>(2.25, 5.5, 26.5, 4.5),
	});

	const GenericMatrix<double, 4, 4> CofactorExpectedResult(
	{
		RowVector(-6.46875, -30.25, -40.6875, 24.15625),
		RowVector(8.984375, 14.25, 35.6875, -26.609375),
		RowVector(-2.109375, 1, 0.3125, -5.703125),
		RowVector(-2.265625, -22.0625, -45.9375, 26.265625),
	});

	const GenericMatrix<double, 4, 4> AdjoinedExpectedResult(
	{
		RowVector(-6.46875, 8.984375, -2.109375, -2.265625),
		RowVector(-30.25, 14.25, 1, -22.0625),
		RowVector(-40.6875, 35.6875, 0.3125, -45.9375),
		RowVector(24.15625, -26.609375, -5.703125, 26.265625),
	});

	const GenericMatrix<double, 4, 4> InverseExpectedResult(
	{
		RowVector(0.20710355177588794402, -0.28764382191095547775, 0.067533766883441720858, 0.072536268134067033544),
		RowVector(0.96848424212106053046, -0.45622811405702851436, -0.03201600800400200101, 0.70635317658829414721),
		RowVector(1.3026513256628314161, -1.1425712856428214108, -0.01000500250125062533, 1.4707353676838419212),
		RowVector(-0.77338669334667333699, 0.85192596298149074551, 0.18259129564782391197, -0.84092046023011505775),
	});

	const GenericMatrix<double, 4, 4> IdentityExpectedResult
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

	Matrix IterateWorkOnMatrices(const Matrix& a, const Matrix& b, double (*action)(double a, double b))
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
	Matrix IterateWorkOnMatrices(const Matrix& a, double b, double(*action)(double a, double b))
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
		return IterateWorkOnMatrices(a, b, [](double a, double b) -> double
			{
				return a + b;
			});
	}
	Matrix Subtract(const Matrix& a, const Matrix& b)
	{
		return IterateWorkOnMatrices(a, b, [](double a, double b) -> double
			{
				return a - b;
			});
	}
	Matrix Divide(const Matrix& a, const Matrix& b)
	{
		return IterateWorkOnMatrices(a, b, [](double a, double b) -> double
			{
				return a / b;
			});
	}
	Matrix Multiply(const Matrix& a, const Matrix& b)
	{
		return IterateWorkOnMatrices(a, b, [](double a, double b) -> double
			{
				return a * b;
			});
	}
	Matrix MultiplyScalar(const Matrix& a, double scalar)
	{
		return IterateWorkOnMatrices(a, scalar, [](double a, double b) -> double
			{
				return a * b;
			});
	}

	template<class T, unsigned int rows, unsigned int columns>
	void ExpectEqual(const VectorBase<T, columns>* expectedValues, const GenericMatrix<double, rows, columns>& actualValues)
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
	void ExpectEqual(const GenericMatrix<T, rows, columns>& expectedValues, const GenericMatrix<T, rows, columns>& actualValues)
	{
		for (unsigned int i = 0; i < actualValues.GetRows(); i++)
		{
			for (unsigned int j = 0; j < actualValues.GetColumns(); j++)
			{
				EXPECT_EQ(expectedValues[i][j], actualValues[i][j]);
			}
		}
	}
	template<class T, unsigned int dimensions>
	void ExpectEqual(const VectorBase<T, dimensions>& a, const VectorBase<T, dimensions>& b)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			EXPECT_EQ(a[i], b[i]);
		}
	}
	void ExpectNear(double expectedValue, double actualValue, double precision = nearComparisonPrecision)
	{
		EXPECT_NEAR(expectedValue, actualValue, precision);
	}
	template<class T, unsigned int rows, unsigned int columns>
	void ExpectNear(const GenericMatrix<T, rows, columns>& expectedValue, const GenericMatrix<T, rows, columns>& actualValue, double precision = nearComparisonPrecision)
	{
		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				EXPECT_NEAR(expectedValue[i][j], actualValue[i][j], nearComparisonPrecision);
			}
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
		GenericMatrix<double, 4, 2> matrixA = MatrixMultiplicationInputA;
		GenericMatrix<double, 2, 4> matrixB = MatrixMultiplicationInputB;
		GenericMatrix<double, 4, 4> expectedResult = MatrixMultiplicationExpectedResult;


		GenericMatrix<double, 4, 4> actualResult = matrixA * matrixB;


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


		Matrix actualResult = BaseMatrix::GetIdentityMatrix<double, 4>();


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
		GenericMatrix<double, 1, 1> d{};

		ExpectTrue(a == b);
		ExpectFalse(a == c);
		ExpectFalse(a == d);
	}

	TEST(MatrixText, Inequality)
	{
		Matrix a = GetTestMatrix(TestValues[0]);
		Matrix b = GetTestMatrix(TestValues[0]);
		Matrix c = GetTestMatrix(TestValues[1]);
		GenericMatrix<double, 1, 1> d{};

		ExpectFalse(a != b);
		ExpectTrue(a != c);
		ExpectTrue(a != d);
	}

	TEST(MatrixTest, VectorMultiplication)
	{
		GenericMatrix<double, 2, 3> matrix
		({
			VectorBase<double, 3>(6, 4, 3),
			VectorBase<double, 3>(0, 1, -2),
		});
		VectorBase<double, 3> vector(3, 0, -1.5);
		VectorBase<double, 2> expectedResult(13.5, 3);


		VectorBase<double, 2> actualResult = matrix * vector;


		ExpectEqual(expectedResult, actualResult);
	}

	TEST(MatrixTest, Minor)
	{
		unsigned int rowToDelete = 1;
		unsigned int columnToDelete = 0;

		GenericMatrix<double, 4, 4> matrix
		({
			VectorBase<double, 4>(2, -5, 3, 6),
			VectorBase<double, 4>(1, 0, 6, 2),
			VectorBase<double, 4>(-1, -2, 5, 7),
			VectorBase<double, 4>(1, 0, 3, 1),
		});
		GenericMatrix<double, 3, 3> expectedResult(
		{
			VectorBase<double, 3>(-5, 3, 6),
			VectorBase<double, 3>(-2, 5, 7),
			VectorBase<double, 3>(0, 3, 1),
		});


		GenericMatrix<double, 3, 3> actualResult = matrix.GetMinor(rowToDelete, columnToDelete);


		ExpectEqual(expectedResult, actualResult);
	}

	TEST(MatrixTest, Determinant)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		double expectedValue = DeterminantExpectedValue;


		double actualValue = matrix.GetDeterminant();


		ExpectNear(expectedValue, actualValue, 1e-4);
	}

	TEST(MatrixTest, CofactorMatrix)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix expectedValues = CofactorExpectedResult;


		Matrix actualValue = matrix.GetCofactorMatrix();


		ExpectEqual(expectedValues, actualValue);
	}

	TEST(MatrixTest, AdjointMatrix)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix expectedValues = AdjoinedExpectedResult;


		Matrix actualValue = matrix.GetAdjointMatrix();


		ExpectEqual(expectedValues, actualValue);
	}

	TEST(MatrixTest, Inverse)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix expectedValues = InverseExpectedResult;


		Matrix actualValues = matrix.GetInverseMatrix();


		ExpectNear(expectedValues, actualValues);
	}
	TEST(MatrixTest, MultiplyingInverseMatrixReturnsIdentity)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix inverse = matrix.GetInverseMatrix();
		Matrix expectedValue = matrix.GetIdentityMatrix();


		Matrix actualValue = matrix * inverse;


		ExpectNear(expectedValue, actualValue);
	}
	TEST(MatrixTest, InverseCommunatitiveMultiplication)
	{
		Matrix matrix = GetTestMatrix(TestValues[0]);
		Matrix inverse = matrix.GetInverseMatrix();


		Matrix a = matrix * inverse;
		Matrix b = inverse * matrix;


		ExpectNear(a, b);
	}
	TEST(MatrixTest, ScaleTransform)
	{

	}
}