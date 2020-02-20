#pragma once

#include <type_traits>
#include <initializer_list>
#include <algorithm>

#include "Exceptions/InvalidArgumentException.h"
#include "Engine/Maths/Vectors/VectorBase.h"
#include "Debugging/IDebugStringReturner.h"
#include "Engine/Quaternion.h"

using namespace ArtemisEngine;
using ArtemisEngine::Maths::Vectors::VectorBase;
using std::initializer_list;

namespace ArtemisEngine::Maths::Matrices
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
				T a = aMatrix[rowIndex][i];
				T b = bMatrix[i][columnIndex];

				T value = a * b;

				dotProduct += aMatrix[rowIndex][i] * bMatrix[i][columnIndex];
			}

			return dotProduct;
		}
	};

	template<class T, unsigned int rows, unsigned int columns>
	class GenericMatrix : BaseMatrix
	{
	public:
		typedef VectorBase<T, columns> RowVector;
		typedef VectorBase<T, rows> ColumnVector;

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
		GenericMatrix(const RowVector(&rowVectors)[N])
		{
			static_assert(N <= rows, "Passed more row vectors to matrix constructor than there are rows");

			for (unsigned int i = 0; i < N; i++)
			{
				SetRow(i, rowVectors[i]);
			}
		}

		// Returns a scale transformation matrix
		template<unsigned int vectorDimensions>
		static GenericMatrix Scale(const VectorBase<T, vectorDimensions>& scale)
		{
			GenericMatrix matrix = BaseMatrix::GetIdentityMatrix<T, rows>();

			for (unsigned int i = 0; i < vectorDimensions; i++)
			{
				matrix[i][i] = scale[i];
			}

			return matrix;
		}

		// Converts a quaternion to a rotation matrix
		static GenericMatrix Rotation(const Quaternion& q)
		{
			if (!q.IsNormalized())
				throw InvalidArgumentException("Quaternion must be normalized when creating rotation matrix");

			GenericMatrix m = BaseMatrix::GetIdentityMatrix<T, rows>();

			const float xx = q.X * (q.X + q.X);
			const float yy = q.Y * (q.Y + q.Y);
			const float wx = q.W * (q.X + q.X);

			const float xy = q.X * (q.Y + q.Y);
			const float yz = q.Y * (q.Z + q.Z);
			const float wy = q.W * (q.Y + q.Y);

			const float xz = q.X * (q.Z + q.Z);
			const float zz = q.Z * (q.Z + q.Z);
			const float wz = q.W * (q.Z + q.Z);

			// We only modify the top-left 3x3 minor of the 4x4 identity matrix
			m[0][0] = 1.0f - (yy + zz);
			m[0][1] = xy + wz;
			m[0][2] = xz - wy;

			m[1][0] = xy - wz;
			m[1][1] = 1.0f - (xx + zz);
			m[1][2] = yz + wx;

			m[2][0] = xz + wy;
			m[2][1] = yz - wx;
			m[2][2] = 1.0f - (xx + yy);
			
			return m;
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

		template<typename = typename std::enable_if<(rows == columns)>::type>
		GenericMatrix GetIdentityMatrix() const
		{
			return BaseMatrix::GetIdentityMatrix<T, rows>();
		}

		// Returns the inverse of the matrix.
		// Requires the matrix to be square.
		GenericMatrix GetInverseMatrix() const
		{
			static_assert(rows == columns, "Cannot get inverse of non-square matrix.");

			GenericMatrix adjoint = GetAdjointMatrix();
			T determinant = GetDeterminant();

			T scalar = 1 / determinant;

			return scalar * adjoint;
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

		// Returns the minor of this matrix.
		// Requires the matrix to be square.
		// Will return a matrix[N - 1, N - 1] with a removed row and column.
		GenericMatrix<T, rows - 1, columns - 1> GetMinor(unsigned int rowToDelete, unsigned int columnToDelete) const
		{
			static_assert(rows == columns, "Cannot get minor of non-square matrix");
			static_assert(rows >= 2, "Cannot get minor of a matrix that has 2 rows or fewer.");
			static_assert(columns >= 2, "Cannot get minor of a matrix that has 2 column or fewer.");
			
			GenericMatrix<T, rows - 1, columns - 1> minor{};

			unsigned int rowIndex = 0;
			for (unsigned int i = 0; i < minor.GetRows(); i++)
			{
				if (rowIndex == rowToDelete)
					rowIndex++;

				unsigned int columnIndex = 0;
				for (unsigned int j = 0; j < minor.GetColumns(); j++)
				{
					if (columnIndex == columnToDelete)
						columnIndex++;


					minor[i][j] = values[rowIndex][columnIndex];


					columnIndex++;
				}

				rowIndex++;
			}

			return minor;
		}

		// Returns the determinant of the matrix
		// Requires the matrix to be square
		T GetDeterminant() const
		{
			static_assert(rows == columns, "Cannot get determinant of non-square matrix");

			if constexpr (rows >= 2 && columns >= 2)
			{
				T determinant{};

				for (unsigned int j = 0; j < columns; j++)
				{
					GenericMatrix<T, rows - 1, columns - 1> minor = GetMinor(0, j);
					T currentValue = values[0][j] * minor.GetDeterminant();

					if ((j & 1) == 1)
						currentValue *= -1;

					determinant += currentValue;
				}

				return determinant;
			}
			else
			{
				return values[0][0];
			}
		}

		// Returns the adjoint of this matrix
		// The adjoint matrix is the transpose of the cofactor matrix
		// Requires the matrix to be square
		GenericMatrix GetAdjointMatrix() const
		{
			return GetCofactorMatrix().GetTranspose();
		}


		// Returns the cofactor of the matrix
		// Requires the matrix to be square
		GenericMatrix GetCofactorMatrix() const
		{
			GenericMatrix cofactor{};

			for (unsigned int i = 0; i < cofactor.GetRows(); i++)
			{
				for (unsigned int j = 0; j < cofactor.GetColumns(); j++)
				{
					cofactor[i][j] = CalculateCofactor(i, j);
				}
			}

			return cofactor;
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
		T CalculateCofactor(unsigned int i, unsigned int j) const
		{
			T det = GetMinor(i, j).GetDeterminant();

			if (((i + j) & 1) == 1)
				det *= -1;

			return det;
		}

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
	GenericMatrix<T, rows, columns> operator*(TScalar scalar, const GenericMatrix<T, rows, columns> matrix)
	{
		return matrix * scalar;
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
	
	template<class T, unsigned int rows, unsigned int columns, unsigned int inputVectorDimensions>
	VectorBase<T, rows> operator*(const VectorBase<T, inputVectorDimensions>& vector, const GenericMatrix<T, rows, columns>& matrix)
	{
		return matrix * vector;
	}
	template<class T, unsigned int rows, unsigned int columns, unsigned int inputVectorDimensions>
	VectorBase<T, rows> operator*(const GenericMatrix<T, rows, columns>& matrix, const VectorBase<T, inputVectorDimensions>& vector)
	{
		VectorBase<T, rows> toReturn;
		unsigned int minRows = rows < inputVectorDimensions ? rows : inputVectorDimensions;
		unsigned int minColumns = rows < inputVectorDimensions ? columns : inputVectorDimensions;

		for (unsigned int i = 0; i < minRows; i++)
		{
			for (unsigned int j = 0; j < minColumns; j++)
			{
				toReturn[i] += matrix[i][j] * vector[j];
			}
		}

		return toReturn;
	}
}