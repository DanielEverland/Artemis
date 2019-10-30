#pragma once

namespace ArtemisEngine::Math::Matrices
{
	template<class T, unsigned int rows, unsigned int columns>
	class MatrixBase
	{
	public:

		// Returns the transpose of this matrix.
		// The transpose turns the columns and rows.
		MatrixBase GetTranspose() const;

		MatrixBase& operator+(MatrixBase& other);

		template<class TScalar>
		MatrixBase& operator*(TScalar scalar);

	private:
		T values[rows, columns];
	};
}