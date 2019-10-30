#include "MatrixBase.h"

using namespace ArtemisEngine::Math::Matrices;

template<class T, unsigned int rows, unsigned int columns>
MatrixBase<T, rows, columns>& MatrixBase<T, rows, columns>::operator+(MatrixBase& other)
{
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < columns; j++)
		{
			this->values[i, j] += other.values[i, j];
		}
	}

	return this;
}

template<class T, unsigned int rows, unsigned int columns>
template<class TScalar>
MatrixBase<T, rows, columns>& MatrixBase<T, rows, columns>::operator*(TScalar scalar)
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
MatrixBase<T, rows, columns> MatrixBase<T, rows, columns>::GetTranspose() const
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