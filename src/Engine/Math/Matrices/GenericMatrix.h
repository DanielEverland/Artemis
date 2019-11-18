#pragma once

namespace ArtemisEngine::Math::Matrices
{
	template<class T, unsigned int rows, unsigned int columns>
	class GenericMatrix : public MatrixBase
	{
	public:
		// Returns the dot product of two matrices
		template<unsigned int otherRows, unsigned int otherColumns>
		static T DotProduct(GenericMatrix& a, GenericMatrix<T, otherRows, otherColumns>& b, unsigned int aRow, unsigned int bColumn);

		// Returns the transpose of this matrix.
		// The transpose turns the columns and rows.
		GenericMatrix GetTranspose() const;

		template<unsigned int otherRows, unsigned int otherColumns>
		GenericMatrix<T, columns, otherRows>& operator*(GenericMatrix<T, otherRows, otherColumns>& other);

		GenericMatrix& operator+(GenericMatrix& other);
		GenericMatrix& operator-(GenericMatrix& other);

		template<class TScalar>
		GenericMatrix& operator*(TScalar scalar);

	protected:
		T values[rows, columns];
	};
}