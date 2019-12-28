#pragma once

#include <cmath>

#include "Exceptions/InvalidArgumentException.h"
#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	class Vector2Base : public VectorWrapper<T, 2>
	{
	public:
		~Vector2Base() = default;
		Vector2Base() : VectorWrapper<T, 2>() { }
		Vector2Base(T x, T y) : VectorWrapper<T, 2>(x, y) { }
		Vector2Base(const VectorWrapper& copy) : VectorWrapper<T, 2>(copy) { }
		Vector2Base(VectorWrapper&& move) : VectorWrapper<T, 2>(move) { }

		Vector2Base& operator=(VectorWrapper& copy)
		{
			this->x = copy.x;
			this->y = copy.y;

			return *this;
		}
		Vector2Base& operator=(VectorWrapper&& move)
		{
			this->x = move.x;
			this->y = move.y;

			move.x = 0;
			move.y = 0;

			return *this;
		}
	};
}