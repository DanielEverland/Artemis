#include <Exceptions/InvalidArgumentException.h>
#include "Vector2Base.h"

using namespace ArtemisEngine::Math;

template<class T>
Vector2Base<T>::Vector2Base()
{
	this->x = 0;
	this->y = 0;
}

template<class T>
Vector2Base<T>::Vector2Base(T x, T y)
{
	this->x = x;
	this->y = y;
}

template<class T>
T& Vector2Base<T>::operator[](int index) const
{
	if (index == 0)
	{
		return x;
	}
	else if (index == 1)
	{
		return y;
	}
	else
	{
		throw new InvalidArgumentException("Attempted to access Vector2Base member using index [" + std::to_string(index) + "], but it is out of range." +
			+"\nValid indexes are as follows: 0 = x, 1 = y");
	}
}