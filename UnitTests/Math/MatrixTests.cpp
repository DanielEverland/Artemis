#include "pch.h"

#include "Engine/Maths/Matrices/GenericMatrix.h"
#include "Engine/Maths/Vectors/VectorBase.h"
#include "Engine/Quaternion.h"
#include "Utility/Comparison/ComparisonUtility.h"
#include "Utility/Comparison/ComparisonUtilityMatrix.h"
#include "Utility/Comparison/ComparisonUtilityVectors.h"

namespace Maths::Matrices
{
	using namespace ArtemisEngine;
	using ArtemisEngine::Maths::Matrices::BaseMatrix;
	using ArtemisEngine::Maths::Matrices::GenericMatrix;
	using ArtemisEngine::Maths::Vectors::VectorBase;

	const unsigned int rows = 4;
	const unsigned int columns = 4;

	typedef VectorBase<double, columns> RowVector;
	typedef VectorBase<double, rows> ColumnVector;
	typedef GenericMatrix<double, rows, columns> Matrix;
	typedef	GenericMatrix<double, 1, columns> RowMatrix;
	typedef	GenericMatrix<double, rows, 1> ColumnMatrix;
	
	TEST(MatrixTest, EmptyConstructor)
	{
		Matrix matrix;


		MatrixExpectEmpty(matrix);
	}
	TEST(MatrixTest, InitializerListConstructor)
	{
		RowVector expectedResult[4]
		{
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		};


		Matrix actualValues(expectedResult);


		MatrixExpectNear(expectedResult, actualValues);
	}
	TEST(MatrixTest, Addition)
	{
		Matrix a
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix b
		({
			RowVector(4.25, -1.25, 3.0, 5.25),
			RowVector(-1.0, 1.25, 2.0, 3.25),
			RowVector(-0.75, -1.25, -2.0, 3.25),
			RowVector(2.50, -1.50, -1.75, 2.0),
		});
		Matrix expectedResult
		({
			RowVector(5.25, 1.25, 1.75, 5.25),
			RowVector(-3.75, 2.50, 2.25, 4.50),
			RowVector(2.50, -2.25, 0.75, 7.50),
			RowVector(-0.5, -2.75, 0.25, 3.0),
		});


		Matrix actualResult = a + b;


		MatrixExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, AdditionAssignment)
	{
		Matrix actualResult
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix b
		({
			RowVector(4.25, -1.25, 3.0, 5.25),
			RowVector(-1.0, 1.25, 2.0, 3.25),
			RowVector(-0.75, -1.25, -2.0, 3.25),
			RowVector(2.50, -1.50, -1.75, 2.0),
		});
		Matrix expectedResult
		({
			RowVector(5.25, 1.25, 1.75, 5.25),
			RowVector(-3.75, 2.50, 2.25, 4.50),
			RowVector(2.50, -2.25, 0.75, 7.50),
			RowVector(-0.5, -2.75, 0.25, 3.0),
		});


		actualResult += b;


		MatrixExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, Subtraction)
	{
		Matrix a
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix b
		({
			RowVector(4.25, -1.25, 3.0, 5.25),
			RowVector(-1.0, 1.25, 2.0, 3.25),
			RowVector(-0.75, -1.25, -2.0, 3.25),
			RowVector(2.50, -1.50, -1.75, 2.0),
		});
		Matrix expectedResult
		({
			RowVector(-3.25, 3.75, -4.25, -5.25),
			RowVector(-1.75, 0, -1.75, -2.0),
			RowVector(4.0, 0.25, 4.75, 1.0),
			RowVector(-5.50, 0.25, 3.75, -1.0),
		});
		

		Matrix actualResult = a - b;


		MatrixExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, SubtractionAssignment)
	{
		Matrix actualResult
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix b
		({
			RowVector(4.25, -1.25, 3.0, 5.25),
			RowVector(-1.0, 1.25, 2.0, 3.25),
			RowVector(-0.75, -1.25, -2.0, 3.25),
			RowVector(2.50, -1.50, -1.75, 2.0),
		});
		Matrix expectedResult
		({
			RowVector(-3.25, 3.75, -4.25, -5.25),
			RowVector(-1.75, 0, -1.75, -2.0),
			RowVector(4.0, 0.25, 4.75, 1.0),
			RowVector(-5.50, 0.25, 3.75, -1.0),
		});


		actualResult -= b;


		MatrixExpectNear(actualResult, expectedResult);
	}
	TEST(MatrixTest, ScalarMultiplication)
	{
		double scalar = 2;
		Matrix matrix
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix expectedResult
		({
			RowVector(2.0, 5.0, -2.50, 0),
			RowVector(-5.50, 2.50, 0.5, 2.50),
			RowVector(6.50, -2.0, 5.50, 8.50),
			RowVector(-6.0, -2.50, 4.0, 2.0)
		});


		Matrix actualResult = matrix * scalar;


		MatrixExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, ScalarMultiplicationAssignment)
	{
		double scalar = 2;
		Matrix actualResult
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix expectedResult
		({
			RowVector(2.0, 5.0, -2.50, 0),
			RowVector(-5.50, 2.50, 0.5, 2.50),
			RowVector(6.50, -2.0, 5.50, 8.50),
			RowVector(-6.0, -2.50, 4.0, 2.0)
		});


		actualResult *= scalar;


		MatrixExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, MatrixMultiplication)
	{
		GenericMatrix<double, 4, 2> matrixA
		({
			VectorBase<double, 2>(1, 2),
			VectorBase<double, 2>(4, -2),
			VectorBase<double, 2>(-5, 6),
			VectorBase<double, 2>(0, 2),
		});
		GenericMatrix<double, 2, 4> matrixB
		({
			VectorBase<double, 4>(1, 2, 3, 4),
			VectorBase<double, 4>(-5, 5, 3, -2),
		});
		GenericMatrix<double, 4, 4> expectedResult
		({
			VectorBase<double, 4>(-9, 12, 9, 0),
			VectorBase<double, 4>(14, -2, 6, 20),
			VectorBase<double, 4>(-35, 20, 3, -32),
			VectorBase<double, 4>(-10, 10, 6, -4),
		});


		GenericMatrix<double, 4, 4> actualResult = matrixA * matrixB;


		MatrixExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, Transpose)
	{
		Matrix expectedResult
		({
			RowVector(1.0, -2.75, 3.25, -3.0),
			RowVector(2.50, 1.25, -1.0, -1.25),
			RowVector(-1.25, 0.25, 2.75, 2.0),
			RowVector(0.0, 1.25, 4.25, 1.0),
		});
		Matrix matrix
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});


		Matrix actualResult = matrix.GetTranspose();


		MatrixExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, Identity)
	{
		Matrix expectedResult
		({
			RowVector(1, 0, 0, 0),
			RowVector(0, 1, 0, 0),
			RowVector(0, 0, 1, 0),
			RowVector(0, 0, 0, 1),
		});


		Matrix actualResult = BaseMatrix::GetIdentityMatrix<double, 4>();


		MatrixExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, MultiplicativeIdentity)
	{
		Matrix matrix
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix expectedResult
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix identity = matrix.GetIdentityMatrix();


		Matrix actualResult = matrix * identity;


		MatrixExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, SquareMatrixCommunitativeIdentityMultiplication)
	{
		Matrix matrix
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix identity = matrix.GetIdentityMatrix();


		Matrix a = matrix * identity;
		Matrix b = identity * matrix;


		MatrixExpectNear(a, b);
	}
	TEST(MatrixTest, SetRow)
	{
		RowVector row(1, 2, 3, 4);
		RowMatrix matrix;


		matrix.SetRow(0, row);


		MatrixExpectRowNear(matrix, row);
	}

	TEST(MatrixTest, SetColumn)
	{
		ColumnVector column(1, 2, 3, 4);
		ColumnMatrix matrix;


		matrix.SetColumn(0, column);


		MatrixExpectColumnNear(matrix, column);
	}

	TEST(MatrixTest, AssignmentOperator)
	{
		Matrix expectedResult
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix actualResult{};


		actualResult = expectedResult;


		MatrixExpectNear(expectedResult, actualResult);
	}

	TEST(MatrixTest, MoveAssignmentOperator)
	{
		RowVector expectedResult[4]
		{
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		};


		Matrix actualResult = std::move(Matrix({ expectedResult }));


		MatrixExpectNear(expectedResult, actualResult);
	}

	TEST(MatrixText, Equality)
	{
		Matrix a
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix b
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix c
		({
			RowVector(4.25, -1.25, 3.0, 5.25),
			RowVector(-1.0, 1.25, 2.0, 3.25),
			RowVector(-0.75, -1.25, -2.0, 3.25),
			RowVector(2.50, -1.50, -1.75, 2.0),
		});
		GenericMatrix<double, 1, 1> d{};


		ExpectTrue(a == b);
		ExpectFalse(a == c);
		ExpectFalse(a == d);
	}

	TEST(MatrixText, Inequality)
	{
		Matrix a
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix b
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix c
		({
			RowVector(4.25, -1.25, 3.0, 5.25),
			RowVector(-1.0, 1.25, 2.0, 3.25),
			RowVector(-0.75, -1.25, -2.0, 3.25),
			RowVector(2.50, -1.50, -1.75, 2.0),
		});
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


		VectorExpectNear(expectedResult, actualResult);
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


		MatrixExpectNear(expectedResult, actualResult);
	}

	TEST(MatrixTest, Determinant)
	{
		Matrix matrix
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		double expectedResult = -31.234375;


		double actualResult = matrix.GetDeterminant();


		ExpectNear(expectedResult, actualResult);
	}

	TEST(MatrixTest, CofactorMatrix)
	{
		Matrix matrix
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix expectedResult
		({
			RowVector(-6.46875, -30.25, -40.6875, 24.15625),
			RowVector(8.984375, 14.25, 35.6875, -26.609375),
			RowVector(-2.109375, 1, 0.3125, -5.703125),
			RowVector(-2.265625, -22.0625, -45.9375, 26.265625),
		});


		Matrix actualResult = matrix.GetCofactorMatrix();


		MatrixExpectNear(expectedResult, actualResult);
	}

	TEST(MatrixTest, AdjointMatrix)
	{
		Matrix matrix
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix expectedResult
		({
			RowVector(-6.46875, 8.984375, -2.109375, -2.265625),
			RowVector(-30.25, 14.25, 1, -22.0625),
			RowVector(-40.6875, 35.6875, 0.3125, -45.9375),
			RowVector(24.15625, -26.609375, -5.703125, 26.265625),
		});


		Matrix actualResult = matrix.GetAdjointMatrix();


		MatrixExpectNear(expectedResult, actualResult);
	}

	TEST(MatrixTest, Inverse)
	{
		Matrix matrix
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix expectedResult
		({
			RowVector(0.20710355177588794402, -0.28764382191095547775, 0.067533766883441720858, 0.072536268134067033544),
			RowVector(0.96848424212106053046, -0.45622811405702851436, -0.03201600800400200101, 0.70635317658829414721),
			RowVector(1.3026513256628314161, -1.1425712856428214108, -0.01000500250125062533, 1.4707353676838419212),
			RowVector(-0.77338669334667333699, 0.85192596298149074551, 0.18259129564782391197, -0.84092046023011505775),
		});


		Matrix actualResult = matrix.GetInverseMatrix();


		MatrixExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, MultiplyingInverseMatrixReturnsIdentity)
	{
		Matrix matrix
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix inverse = matrix.GetInverseMatrix();
		Matrix expectedResult = matrix.GetIdentityMatrix();


		Matrix actualResult = matrix * inverse;


		MatrixExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, InverseCommunatitiveMultiplication)
	{
		Matrix matrix
		({
			RowVector(1.0, 2.50, -1.25, 0),
			RowVector(-2.75, 1.25, 0.25, 1.25),
			RowVector(3.25, -1.0, 2.75, 4.25),
			RowVector(-3.0, -1.25, 2.0, 1.0)
		});
		Matrix inverse = matrix.GetInverseMatrix();


		Matrix a = matrix * inverse;
		Matrix b = inverse * matrix;


		MatrixExpectNear(a, b);
	}
	TEST(MatrixTest, ScaleTransform)
	{
		VectorBase<double, 3> positionToScale(-4, -4, 0);
		VectorBase<double, 3> expectedResult(-2, -8, 0);
		VectorBase<double, 3> scale(0.5, 2, 1);
		Matrix matrix = Matrix::Scale(scale);


		VectorBase<double, 3> actualResult = matrix * positionToScale;
		

		VectorExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, QuaternionToMatrix)
	{
		Quaternion quaternion(1, 0.5, -0.2, 1);

		quaternion = quaternion.GetNormalized();

		Matrix expectedResult
		({
			RowVector(0.74672489082969429, 0.26200872659683228, -0.611353711790393, 0),
			RowVector(0.611353711790393, 0.091703057289123535, 0.7860262008733625, 0),
			RowVector(0.26200872659683228, -0.9606986899563319, -0.091703057289123535, 0),
			RowVector(0, 0, 0, 1)
		});

		Matrix actualResult = Matrix::Rotation(quaternion);


		MatrixExpectNear(expectedResult, actualResult);
	}
	TEST(MatrixTest, QuaternionToMatrixNonNormalizedException)
	{
		ExpectThrow(Matrix::Rotation(Quaternion(1, 0.5, -0.2, 1)), InvalidArgumentException);
	}
	TEST(MatrixTest, PointRotation)
	{
		Vector3 point(2.5, -3.75, 1.25);
		Vector3 expectedResult(3.6154770433224894, 2.8343231363825439, 0.877461171662137);
		Quaternion rotationQuaternion = Quaternion::FromEuler(-26.35, 32.34, 96.55);
		Matrix rotationMatrix = Matrix::Rotation(rotationQuaternion);


		Vector3 actualResult = rotationMatrix.TransformPoint(point);


		VectorExpectNear(expectedResult, actualResult);
	}
}