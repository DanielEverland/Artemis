#include <Exceptions/InvalidArgumentException.h>
#include "MatrixBase.h"

using namespace ArtemisEngine::Math::Matrices;

template<class T>
T MatrixBase::DotProduct(MatrixBase& a, MatrixBase& b, unsigned int aRow, unsigned int bColumn)
{
	if (a.GetColumns() != b.GetRows())
		throw InvalidArgumentException("Can't get dot product of two matrices. Matrix A column count should be equal to matrix B row count");

	T value;
	unsigned int length = a.GetColumns();

	for (unsigned int i = 0; i < length; i++)
	{
		value += a(aRow, i) * b(i, bColumn);
	}

	return value;
}