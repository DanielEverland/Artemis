#pragma once

namespace ArtemisEngine::Math::Matrices
{
	class MatrixBase
	{
	public:
		// Returns the dot product of two matrices
		template<class T>
		static T DotProduct(MatrixBase& a, MatrixBase& b, unsigned int aRow, unsigned int bColumn);

	protected:

		template<class T>
		T virtual GetValue(unsigned int i, unsigned int j) const = 0;

		unsigned int virtual GetRows() const = 0;
		unsigned int virtual GetColumns() const = 0;
	};
}