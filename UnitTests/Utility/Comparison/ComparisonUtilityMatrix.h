#pragma once

#include "Engine/Math/Matrices/GenericMatrix.h"

namespace ArtemisEngine::UnitTests::Comparisons
{
	using ArtemisEngine::Math::Matrices::GenericMatrix;

	template<class T, unsigned int rows, unsigned int columns>
	void ExpectEmpty(const GenericMatrix<T, rows, columns>& matrix)
	{
		for (unsigned int i = 0; i < matrix.GetRows(); i++)
		{
			for (unsigned j = 0; j < matrix.GetColumns(); j++)
			{
				EXPECT_EQ(0, matrix[i][j]);
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
	template<class T, unsigned int dimensions>
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
	template<class T, unsigned int dimensions>
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
	template<class T, unsigned int dimensions>
	Matrix Add(const Matrix& a, const Matrix& b)
	{
		return IterateWorkOnMatrices(a, b, [](double a, double b) -> double
			{
				return a + b;
			});
	}
	template<class T, unsigned int dimensions>
	Matrix Subtract(const Matrix& a, const Matrix& b)
	{
		return IterateWorkOnMatrices(a, b, [](double a, double b) -> double
			{
				return a - b;
			});
	}
	template<class T, unsigned int dimensions>
	Matrix Divide(const Matrix& a, const Matrix& b)
	{
		return IterateWorkOnMatrices(a, b, [](double a, double b) -> double
			{
				return a / b;
			});
	}
	template<class T, unsigned int dimensions>
	Matrix Multiply(const Matrix& a, const Matrix& b)
	{
		return IterateWorkOnMatrices(a, b, [](double a, double b) -> double
			{
				return a * b;
			});
	}
	template<class T, unsigned int dimensions>
	Matrix MultiplyScalar(const Matrix& a, double scalar)
	{
		return IterateWorkOnMatrices(a, scalar, [](double a, double b) -> double
			{
				return a * b;
			});
	}
}