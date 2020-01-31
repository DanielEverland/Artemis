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
}