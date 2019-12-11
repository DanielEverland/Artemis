#pragma once

#include <cmath>

#include "Exceptions/InvalidArgumentException.h"
#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	class Vector2Base : public VectorBase<T, 2>
	{
	public:
		Vector2Base()
		{
		}
		Vector2Base(T x, T y)
		{
			(*this)[0] = x;
			(*this)[1] = y;
		}
		Vector2Base(const VectorBase<T, 2> other)
		{
			(*this)[0] = other[0];
			(*this)[1] = other[1];
		}
	};
}