#include <Exceptions/DivideByZeroException.h>
#include <algorithm>
#include <cmath>

#include "VectorBase.h"


using ArtemisEngine::Math::VectorBase;

template<class T, unsigned int dimensions>
T& VectorBase<T, dimensions>::SqrMagnitude() const
{
	return DotProduct(this, this);
}

template<class T, unsigned int dimensions>
T& VectorBase<T, dimensions>::Magnitude() const
{
	return std::sqrt(SqrMagnitude());
}

template<class T, unsigned int dimensions>
T& VectorBase<T, dimensions>::DotProduct(VectorBase& a, VectorBase& b)
{
	T value;

	for (int i = 0; i < dimensions; i++)
		value = a[i] * b[i];

	return std::clamp(value, -1, 1);
}

template<class T, unsigned int dimensions>
VectorBase<T, dimensions>& VectorBase<T, dimensions>::Normalized() const
{
	T length = Magnitude();

	if (length == 0)
		throw DivideByZeroException("Unable to get unit vector of vector with length 0");

	VectorBase newVector();

	for (int i = 0; i < dimensions; i++)
		newVector[i] = this[i] / length;

	return newVector;
}

// --------------------------------------------------- //
// ----------------- SCALAR ADDITION ----------------- //
// --------------------------------------------------- //
template<class T, unsigned int dimensions>
template<class TValue>
VectorBase<T, dimensions>& VectorBase<T, dimensions>::operator+(TValue value)
{
	for (int i = 0; i < dimensions; i++)
		this[i] + value;

	return this;
}
template<class T, unsigned int dimensions>
VectorBase<T, dimensions>& VectorBase<T, dimensions>::operator+(VectorBase<T, dimensions>& vector)
{
	for (int i = 0; i < dimensions; i++)
		this[i] + vector[i];

	return this;
}

template<class T, unsigned int dimensions>
template<class TValue>
VectorBase<T, dimensions>& VectorBase<T, dimensions>::operator-(TValue value)
{
	for (int i = 0; i < dimensions; i++)
		this[i] - value;

	return this;
}
template<class T, unsigned int dimensions>
VectorBase<T, dimensions>& VectorBase<T, dimensions>::operator-(VectorBase<T, dimensions>& vector)
{
	for (int i = 0; i < dimensions; i++)
		this[i] - vector[i];

	return this;
}

template<class T, unsigned int dimensions>
template<class TValue>
VectorBase<T, dimensions>& VectorBase<T, dimensions>::operator*(TValue value)
{
	for (int i = 0; i < dimensions; i++)
		this[i] * value;

	return this;
}
template<class T, unsigned int dimensions>
VectorBase<T, dimensions>& VectorBase<T, dimensions>::operator*(VectorBase<T, dimensions>& vector)
{
	for (int i = 0; i < dimensions; i++)
		this[i] * vector[i];

	return this;
}

template<class T, unsigned int dimensions>
template<class TValue>
VectorBase<T, dimensions>& VectorBase<T, dimensions>::operator/(TValue value)
{
	for (int i = 0; i < dimensions; i++)
		this[i] / value;

	return this;
}
template<class T, unsigned int dimensions>
VectorBase<T, dimensions>& VectorBase<T, dimensions>::operator/(VectorBase<T, dimensions>& vector)
{
	for (int i = 0; i < dimensions; i++)
		this[i] / vector[i];

	return this;
}