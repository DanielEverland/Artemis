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
		~Vector2Base() = default;
		Vector2Base() : VectorBase<T, 2>() { }
		Vector2Base(T x, T y) : VectorBase<T, 2>(x, y) { }
		Vector2Base(const VectorBase& copy) : VectorBase<T, 2>(copy) { }
		Vector2Base(VectorBase&& move) : VectorBase<T, 2>(move) { }

		Vector2Base& operator=(const VectorBase& copy)
		{
			this->x = copy.x;
			this->y = copy.y;

			return *this;
		}
		Vector2Base& operator=(VectorBase&& move)
		{
			this->x = move.x;
			this->y = move.y;

			move.x = 0;
			move.y = 0;

			return *this;
		}
	};
}