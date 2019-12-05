#pragma once

#include <Exceptions/InvalidArgumentException.h>

#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	struct Vector2Base : public VectorBase<T, 2>
	{
	public:
		Vector2Base()
		{
		}
		Vector2Base(T x, T y)
		{
			this[0] = x;
			this[1] = y;
		}
	};
}