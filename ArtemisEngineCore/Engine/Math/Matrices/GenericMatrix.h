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
	class GenericMatrix
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
					transpose->values[j, i] = this->values[i, j];
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

	template<class T, unsigned int aRows, unsigned int aColumns, unsigned int bRows, unsigned int bColumns>
	GenericMatrix<T, bRows, aColumns> operator*(const GenericMatrix<T, aRows, aColumns>& a, const GenericMatrix<T, bRows, bColumns>& b)
	{
		if (bRows != aColumns)
			throw InvalidArgumentException("Cannot define matrix multiplication when a's number of columns isn't equal to b's number of rows.");

		unsigned int newRowCount = bRows;
		unsigned int newColumnCount = aColumns;

		GenericMatrix<T, newRowCount, newColumnCount> newMatrix;

		for (unsigned int i = 0; i < newRowCount; i++)
		{
			for (unsigned int j = 0; j < newColumnCount; j++)
			{
				newMatrix[i, j] = GenericMatrix::DotProduct(a, b, i, j);
			}
		}

		return newMatrix;
	}

	template<class T, unsigned int rows, unsigned int columns, class TScalar>
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
	template<class T, unsigned int rows, unsigned int columns, class TScalar>
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
}