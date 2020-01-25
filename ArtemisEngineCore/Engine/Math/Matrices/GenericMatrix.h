#pragma once

#include <type_traits>
#include <initializer_list>
#include <algorithm>

#include "Exceptions/InvalidArgumentException.h"
#include "Engine/Math/Vectors/VectorBase.h"
#include "Debugging/IDebugStringReturner.h"

using ArtemisEngine::Math::Vectors::VectorBase;
using std::initializer_list;

namespace ArtemisEngine::Math::Matrices
{
	template<class T, unsigned int rows, unsigned int columns>
	class GenericMatrix;

	class BaseMatrix
	{
	public:

		template<class T, unsigned int dimensions>
		static GenericMatrix<T, dimensions, dimensions> GetIdentityMatrix()
		{
			GenericMatrix<T, dimensions, dimensions> matrix{};

			for (unsigned int i = 0; i < dimensions; i++)
			{
				for (unsigned int j = 0; j < dimensions; j++)
				{
					if (j == i)
						matrix[i][j] = 1;
					else
						matrix[i][j] = 0;
				}
			}

			return matrix;
		}

		template <class T, unsigned int aColumnsAndbRows, unsigned int aRows, unsigned int bColumns>
		static T CalculateDotProduct(
			const GenericMatrix<T, aRows, aColumnsAndbRows>& aMatrix, const GenericMatrix<T, aColumnsAndbRows, bColumns>& bMatrix,
			unsigned int rowIndex, unsigned int columnIndex, unsigned int length)
		{
			T dotProduct{};

			for (unsigned int i = 0; i < length; i++)
			{
				dotProduct += aMatrix[rowIndex][i] * bMatrix[i][columnIndex];
			}

			return dotProduct;
		}
	};

	template<class T, unsigned int rows, unsigned int columns>
	class GenericMatrix : BaseMatrix
	{
	public:
		~GenericMatrix() = default;
		GenericMatrix() = default;
		
		GenericMatrix(const GenericMatrix& copy)
		{
			for (unsigned int i = 0; i < rows; i++)
			{
				for (unsigned int j = 0; j < columns; j++)
				{
					values[i][j] = copy.values[i][j];
				}
			}
		}
		GenericMatrix(GenericMatrix&& move)
		{
			for (unsigned int i = 0; i < rows; i++)
			{
				for (unsigned int j = 0; j < columns; j++)
				{
					values[i][j] = move.values[i][j];

					move.values[i][j] = 0;
				}
			}
		}
		
		template<std::size_t N>
		GenericMatrix(const VectorBase<T, columns>(&rowVectors)[N])
		{
			static_assert(N <= rows, "Passed more row vectors to matrix constructor than there are rows");

			for (unsigned int i = 0; i < N; i++)
			{
				SetRow(i, rowVectors[i]);
			}
		}

		T* operator[](int rowIndex)
		{
			return values[rowIndex];
		}
		const T* operator[](int rowIndex) const
		{
			return values[rowIndex];
		}

		constexpr unsigned int GetRows() const
		{
			return rows;
		}

		constexpr unsigned int GetColumns() const
		{
			return columns;
		}

		T GetValue(unsigned int row, unsigned int column)
		{
			return values[row][column];
		}

		void SetRow(int rowIndex, VectorBase<T, columns> rowValues)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				values[rowIndex][j] = rowValues[j];
			}
		}
		void SetColumn(int columnIndex, VectorBase<T, rows> columnValues)
		{
			for (unsigned int i = 0; i < rows; i++)
			{
				values[i][columnIndex] = columnValues[i];
			}
		}

		// Returns the transpose of this matrix.
		// The transpose turns the columns and rows.
		GenericMatrix GetTranspose() const
		{
			GenericMatrix<T, columns, rows> transpose;

			for (unsigned int i = 0; i < rows; i++)
			{
				for (unsigned int j = 0; j < columns; j++)
				{
					transpose[j][i] = values[i][j];
				}
			}

			return transpose;
		}

		GenericMatrix& operator=(GenericMatrix& copy)
		{
			for (unsigned int i = 0; i < rows; i++)
			{
				for (unsigned int j = 0; j < columns; j++)
				{
					values[i][j] = copy.values[i][j];
				}
			}

			return *this;
		}
		GenericMatrix& operator=(GenericMatrix&& move)
		{
			for (unsigned int i = 0; i < rows; i++)
			{
				for (unsigned int j = 0; j < columns; j++)
				{
					values[i][j] = move.values[i][j];

					move.values[i][j] = 0;
				}
			}

			return *this;
		}

	private:
		T values[rows][columns] = { };
	};

	template<class T, unsigned int rows, unsigned int columns>
	GenericMatrix<T, rows, columns> operator+(const GenericMatrix<T, rows, columns>& a, const GenericMatrix<T, rows, columns>& b)
	{
		GenericMatrix<T, rows, columns> newMatrix;

		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				newMatrix[i][j] = a[i][j] + b[i][j];
			}
		}

		return newMatrix;
	}

	template<class T, unsigned int rows, unsigned int columns>
	GenericMatrix<T, rows, columns> operator+=(GenericMatrix<T, rows, columns>& a, const GenericMatrix<T, rows, columns>& b)
	{
		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				a[i][j] += b[i][j];
			}
		}

		return a;
	}

	template<class T, unsigned int rows, unsigned int columns>
	GenericMatrix<T, rows, columns> operator-(const GenericMatrix<T, rows, columns>& a, const GenericMatrix<T, rows, columns>& b)
	{
		GenericMatrix<T, rows, columns> newMatrix;

		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				newMatrix[i][j] = a[i][j] - b[i][j];
			}
		}
		
		return newMatrix;
	}

	template<class T, unsigned int rows, unsigned int columns>
	GenericMatrix<T, rows, columns> operator-=(GenericMatrix<T, rows, columns>& a, const GenericMatrix<T, rows, columns>& b)
	{
		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				a[i][j] -= b[i][j];
			}
		}

		return a;
	}

	template<class T, unsigned int rows, unsigned int columns, class TScalar, typename std::enable_if<std::is_arithmetic<TScalar>::value>::type * = nullptr>
	GenericMatrix<T, rows, columns> operator*(const GenericMatrix<T, rows, columns> matrix, TScalar scalar)
	{
		GenericMatrix<T, rows, columns> toReturn;

		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				toReturn[i][j] = matrix[i][j] * scalar;
			}
		}

		return toReturn;
	}
	template<class T, unsigned int rows, unsigned int columns, class TScalar, typename std::enable_if<std::is_arithmetic<TScalar>::value>::type * = nullptr>
	GenericMatrix<T, rows, columns> operator*=(GenericMatrix<T, rows, columns>& matrix, TScalar scalar)
	{
		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				matrix[i][j] *= scalar;
			}
		}

		return matrix;
	}

	template<class T, unsigned int aColumnsAndbRows, unsigned int aRows, unsigned int bColumns>
	GenericMatrix<T, aRows, bColumns> operator*(const GenericMatrix<T, aRows, aColumnsAndbRows>& aMatrix, const GenericMatrix<T, aColumnsAndbRows, bColumns>& bMatrix)
	{
		GenericMatrix<T, aRows, bColumns> toReturn;

		for (unsigned int i = 0; i < aRows; i++)
		{
			for (unsigned int j = 0; j < bColumns; j++)
			{
				toReturn[i][j] = BaseMatrix::CalculateDotProduct<T, aColumnsAndbRows, aRows, bColumns>(aMatrix, bMatrix, i, j, aColumnsAndbRows);
			}
		}

		return toReturn;
	}

	template<class T, unsigned int aRows, unsigned int aColumns, unsigned int bRows, unsigned int bColumns>
	bool operator==(const GenericMatrix<T, aRows, aColumns>& aMatrix, const GenericMatrix<T, bRows, bColumns>& bMatrix)
	{
		if (aRows != bRows || aColumns != bColumns)
			return false;

		for (unsigned int i = 0; i < aMatrix.GetRows(); i++)
		{
			for (unsigned int j = 0; j < aMatrix.GetColumns(); j++)
			{
				if (aMatrix[i][j] != bMatrix[i][j])
					return false;
			}
		}

		return true;
	}

	template<class T, unsigned int aRows, unsigned int aColumns, unsigned int bRows, unsigned int bColumns>
	bool operator!=(const GenericMatrix<T, aRows, aColumns>& aMatrix, const GenericMatrix<T, bRows, bColumns>& bMatrix)
	{
		return !(aMatrix == bMatrix);
	}
}