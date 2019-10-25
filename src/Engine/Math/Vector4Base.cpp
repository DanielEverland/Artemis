#include <Exceptions/InvalidArgumentException.h>
#include "Vector4Base.h"

using namespace ArtemisEngine::Math;

template<class T>
T& Vector4Base<T>::operator[](int index) const
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
	else if (index == 3)
	{
		return w;
	}
	else
	{
		throw new InvalidArgumentException("Attempted to access Vector4Base member using index [" + std::to_string(index) + "], but it is out of range." +
			+"\nValid indexes are as follows: 0 = x, 1 = y, 2 = z, 3 = w");
	}
}

template<class T>
Vector4Base<T>::Vector4Base()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

template<class T>
Vector4Base<T>::Vector4Base(T x, T y)
{
	this->x = x;
	this->y = y;
	this->z = 0;
	this->w = 0;
}

template<class T>
Vector4Base<T>::Vector4Base(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 0;
}

template<class T>
Vector4Base<T>::Vector4Base(T x, T y, T z, T w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}