#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	class Vector4Base : public VectorWrapper<T, 4>
	{
	public:
		~Vector4Base() = default;
		Vector4Base() : VectorWrapper<T, 4>() { }
		Vector4Base(T x, T y) : VectorWrapper<T, 4>(x, y) { }
		Vector4Base(T x, T y, T z) : VectorWrapper<T, 4>(x, y, z) { }
		Vector4Base(T x, T y, T z, T w) : VectorWrapper<T, 4>(x, y, z, w) { }
		Vector4Base(const VectorWrapper& copy) : VectorWrapper<T, 4>(copy) { }
		Vector4Base(VectorWrapper&& move) : VectorWrapper<T, 4>(move) { }

		Vector4Base& operator=(VectorWrapper& copy)
		{
			this->x = copy.x;
			this->y = copy.y;
			this->z = copy.z;
			this->w = copy.w;

			return *this;
		}
		Vector4Base& operator=(VectorWrapper&& move)
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
