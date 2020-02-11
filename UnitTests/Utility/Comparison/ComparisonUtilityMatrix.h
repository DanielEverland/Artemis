#pragma once

#include "ComparisonUtility.h"
#include "Engine/Maths/Matrices/GenericMatrix.h"

#define MatrixExpectEmpty(matrix) \
for (unsigned int i = 0; i < matrix.GetRows(); i++) \
	for (unsigned int j = 0; j < matrix.GetColumns(); j++) \
		TempExpectEqual(0, matrix[i][j]);

#define MatrixExpectRowNear(matrix, row) \
for (unsigned int j = 0; j < matrix.GetColumns(); j++) \
	TempExpectNear(matrix[0][j], row[j]);

#define MatrixExpectColumnNear(matrix, row) \
for (unsigned int i = 0; i < matrix.GetColumns(); i++) \
	TempExpectNear(matrix[i][0], row[i]);
	
#define MatrixExpectNear(expectedResult, actualResult) \
for (unsigned int i = 0; i < actualResult.GetRows(); i++) \
	for (unsigned int j = 0; j < actualResult.GetColumns(); j++) \
		TempExpectNear(expectedResult[i][j], actualResult[i][j]);


namespace ArtemisEngine::UnitTests::Comparisons
{
	using ArtemisEngine::Maths::Matrices::GenericMatrix;

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
	void ExpectNear(double expectedValue, double actualValue, double precision = NearComparisonPrecision)
	{
		EXPECT_NEAR(expectedValue, actualValue, precision);
	}
	template<class T, unsigned int rows, unsigned int columns>
	void ExpectNear(const GenericMatrix<T, rows, columns>& expectedValue, const GenericMatrix<T, rows, columns>& actualValue, double precision = NearComparisonPrecision)
	{
		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				EXPECT_NEAR(expectedValue[i][j], actualValue[i][j], NearComparisonPrecision);
			}
		}
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
	template<class T, unsigned int rows, unsigned int columns>
	GenericMatrix<T, rows, columns> IterateWorkOnMatrices(const GenericMatrix<T, rows, columns>& a, const GenericMatrix<T, rows, columns>& b, double (*action)(double a, double b))
	{
		GenericMatrix<T, rows, columns> output;

		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				output[i][j] += action(a[i][j], b[i][j]);
			}
		}

		return output;
	}
	template<class T, unsigned int rows, unsigned int columns>
	GenericMatrix<T, rows, columns> IterateWorkOnMatrices(const GenericMatrix<T, rows, columns>& a, double b, double(*action)(double a, double b))
	{
		GenericMatrix<T, rows, columns> output;

		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				output[i][j] += action(a[i][j], b);
			}
		}

		return output;
	}
	template<class T, unsigned int rows, unsigned int columns>
	GenericMatrix<T, rows, columns> AddMatrices(const GenericMatrix<T, rows, columns>& a, const GenericMatrix<T, rows, columns>& b)
	{
		return IterateWorkOnMatrices(a, b, [](double a, double b) -> double
			{
				return a + b;
			});
	}
	template<class T, unsigned int rows, unsigned int columns>
	GenericMatrix<T, rows, columns> SubtractMatrices (const GenericMatrix<T, rows, columns>& a, const GenericMatrix<T, rows, columns>& b)
	{
		return IterateWorkOnMatrices(a, b, [](double a, double b) -> double
			{
				return a - b;
			});
	}
	template<class T, unsigned int rows, unsigned int columns>
	GenericMatrix<T, rows, columns> DivideMatrices(const GenericMatrix<T, rows, columns>& a, const GenericMatrix<T, rows, columns>& b)
	{
		return IterateWorkOnMatrices(a, b, [](double a, double b) -> double
			{
				return a / b;
			});
	}
	template<class T, unsigned int rows, unsigned int columns>
	GenericMatrix<T, rows, columns> MultiplyMatrices(const GenericMatrix<T, rows, columns>& a, const GenericMatrix<T, rows, columns>& b)
	{
		return IterateWorkOnMatrices(a, b, [](double a, double b) -> double
			{
				return a * b;
			});
	}
	template<class T, unsigned int rows, unsigned int columns>
	GenericMatrix<T, rows, columns> MatrixMultiplyScalar(const GenericMatrix<T, rows, columns>& a, double scalar)
	{
		return IterateWorkOnMatrices(a, scalar, [](double a, double b) -> double
			{
				return a * b;
			});
	}
}