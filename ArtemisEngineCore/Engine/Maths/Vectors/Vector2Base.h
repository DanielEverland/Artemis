#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Maths::Vectors
{
	template<class T>
	class Vector2Base : public VectorBase<T, 2>
	{
	public:
		~Vector2Base() = default;
		Vector2Base() : VectorBase<T, 2>() { }
		Vector2Base(T x, T y) : VectorBase<T, 2>(x, y) { }
		Vector2Base(const VectorBase<T, 2>& copy) : VectorBase<T, 2>(copy) { }
		Vector2Base(VectorBase<T, 2>&& move) : VectorBase<T, 2>(move) { }

		Vector2Base& operator=(VectorBase<T, 2>& copy)
		{
			this->X = copy.X;
			this->Y = copy.Y;

			return *this;
		}
		Vector2Base& operator=(VectorBase<T, 2>&& move)
		{
			this->X = move.X;
			this->Y = move.Y;

			move.X = 0;
			move.Y = 0;

			return *this;
		}
	};
}
