#include <Exceptions/InvalidArgumentException.h>
#include "GenericMatrix.h";

using namespace ArtemisEngine::Math::Matrices;

template<class T, unsigned int rows, unsigned int columns>
template<unsigned int otherRows, unsigned int otherColumns>
T GenericMatrix<T, rows, columns>::DotProduct(GenericMatrix& a, GenericMatrix<T, otherRows, otherColumns>& b, unsigned int aRow, unsigned int bColumn)
{
	if (rows != otherColumns)
		throw InvalidArgumentException("Cannot take dot product of two matrices. Matrix A's numnber of row must be equal to Matrix B's number of columns");

	T result;

	for (int i = 0; i < rows; i++)
	{
		result += a[aRow, i] * b[i, bColumn];
	}
}

template<class T, unsigned int rows, unsigned int columns>
template<class TScalar>
GenericMatrix<T, rows, columns>& GenericMatrix<T, rows, columns>::operator*(TScalar scalar)
{
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < columns; j++)
		{
			this->values[i, j] *= scalar;
		}
	}

	return this;
}

template<class T, unsigned int rows, unsigned int columns>
GenericMatrix<T, rows, columns> GenericMatrix<T, rows, columns>::GetTranspose() const
{
	MatrixBase<T, columns, rows> transpose;

	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < columns; j++)
		{
			transpose->values[j, i] = this->values[i, j];
		}
	}

	return transpose;
}

template<class T, unsigned int rows, unsigned int columns>
template<unsigned int otherRows, unsigned int otherColumns>
GenericMatrix<T, columns, otherRows>& GenericMatrix<T, rows, columns>::operator*(GenericMatrix<T, otherRows, otherColumns>& other)
{
	if (this->GetColumns() != other.GetRows())
		throw InvalidArgumentException("Cannot define matrix multiplication when a's number of columns isn't equal to b's number of rows.");

	unsigned int newRowCount = other.GetRows();
	unsigned int newColumnCount = columns;

	GenericMatrix<T, newRowCount, newColumnCount> newMatrix;

	for (unsigned int i = 0; i < newRowCount; i++)
	{
		for (unsigned int j = 0; j < newColumnCount; j++)
		{
			newMatrix[i, j] = MatrixBase::DotProduct(this, other, i, j);
		}
	}

	return newMatrix;
}

template<class T, unsigned int rows, unsigned int columns>
GenericMatrix<T, rows, columns>& GenericMatrix<T, rows, columns>::operator+(GenericMatrix& other)
{
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < columns; j++)
		{
			this->values[i, j] += other[i, j];
		}
	}
}

template<class T, unsigned int rows, unsigned int columns>
GenericMatrix<T, rows, columns>& GenericMatrix<T, rows, columns>::operator-(GenericMatrix& other)
{
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < columns; j++)
		{
			this->values[i, j] -= other[i, j];
		}
	}
}

template<class T, unsigned int rows, unsigned int columns>
T GenericMatrix<T, rows, columns>::GetValue(int i, int j) const
{
	return this->values[i, j];
}