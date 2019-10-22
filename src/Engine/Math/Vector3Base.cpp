#include <Exceptions/InvalidArgumentException.h>
#include "Vector3Base.h"

using ArtemisEngine::Math::Vector3Base;

template<class T>
Vector3Base<T>::Vector3Base()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

template<class T>
Vector3Base<T>::Vector3Base(T x, T y)
{
	this->x = x;
	this->y = y;
	this->z = 0;
}

template<class T>
Vector3Base<T>::Vector3Base(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template<class T>
T& Vector3Base<T>::operator[](int index) const
{
	if (index == 0)
	{
		return x;
	}
	else if (index == 1)
	{
		return y;
	}
	else if (index == 2)
	{
		return z;
	}
	else
	{
		throw new InvalidArgumentException("Attempted to access Vector3Base member using index [" + std::to_string(index) + "], but it is out of range." +
			+ "\nValid indexes are as follows: 0 = x, 1 = y, 2 = z");
	}
}

template<class T>
Vector3Base<T>& Vector3Base<T>::GetCrossProduct(Vector3Base& a, Vector3Base& b)
{
	return Vector3Base<T>(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}