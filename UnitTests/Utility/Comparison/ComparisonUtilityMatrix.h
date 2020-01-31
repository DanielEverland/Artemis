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
}