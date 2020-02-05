#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Maths::Vectors
{
	template<class T>
	class Vector4Base : public VectorBase<T, 4>
	{
	public:
		~Vector4Base() = default;
		Vector4Base() : VectorBase<T, 4>() { }
		Vector4Base(T x, T y) : VectorBase<T, 4>(x, y) { }
		Vector4Base(T x, T y, T z) : VectorBase<T, 4>(x, y, z) { }
		Vector4Base(T x, T y, T z, T w) : VectorBase<T, 4>(x, y, z, w) { }
		Vector4Base(const VectorBase<T, 4>& copy) : VectorBase<T, 4>(copy) { }
		Vector4Base(VectorBase<T, 4>&& move) : VectorBase<T, 4>(move) { }

		Vector4Base& operator=(VectorBase<T, 4>& copy)
		{
			this->x = copy.x;
			this->y = copy.y;
			this->z = copy.z;
			this->w = copy.w;

			return *this;
		}
		Vector4Base& operator=(VectorBase<T, 4>&& move)
		{
			this->x = move.x;
			this->y = move.y;
			this->z = move.z;
			this->w = move.w;

			move.x = 0;
			move.y = 0;
			move.z = 0;
			move.w = 0;

			return *this;
		}
	};
}
