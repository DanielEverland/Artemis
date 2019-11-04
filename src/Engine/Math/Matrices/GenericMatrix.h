#pragma once

#include "MatrixBase.h"

namespace ArtemisEngine::Math::Matrices
{
	template<class T, unsigned int rows, unsigned int columns>
	class GenericMatrix : public MatrixBase
	{
	public:

		// Returns the transpose of this matrix.
		// The transpose turns the columns and rows.
		GenericMatrix GetTranspose() const;

		GenericMatrix& operator+(MatrixBase& other);

		MatrixBase& operator*(MatrixBase& other);

		template<class TScalar>
		GenericMatrix& operator*(TScalar scalar);

	protected:
		T values[rows, columns];

		T operator()(unsigned int i, unsigned int j) const;

		unsigned int GetRows() const override;
		unsigned int GetColumns() const override;
	};
}