#pragma once

#include <cmath>

#include "Exceptions/InvalidArgumentException.h"
#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	class Vector2Base : public VectorWrapper<T, 2>
	{
		using VectorWrapper::VectorWrapper;

	public:
		Vector2Base(const VectorWrapper<T, 2> copy)
		{
			this->x = copy.x;
			this->y = copy.y;
		}
	};
}