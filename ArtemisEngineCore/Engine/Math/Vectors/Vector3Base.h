#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	class Vector3Base : public VectorBase<T, 3>
	{
	public:
		~Vector3Base() = default;
		Vector3Base() : VectorBase<T, 3>() { }
		Vector3Base(T x, T y) : VectorBase<T, 3>(x, y) { }
		Vector3Base(T x, T y, T z) : VectorBase<T, 3>(x, y, z) { }
		Vector3Base(const VectorBase& copy) : VectorBase<T, 3>(copy) { }
		Vector3Base(VectorBase&& move) : VectorBase<T, 3>(move) { }

		Vector3Base& operator=(VectorBase& copy)
		{
			this->x = copy.x;
			this->y = copy.y;
			this->z = copy.z;

			return *this;
		}
		Vector3Base& operator=(VectorBase&& move)
		{
			this->x = move.x;
			this->y = move.y;
			this->z = move.z;

			move.x = 0;
			move.y = 0;
			move.z = 0;

			return *this;
		}
	};
}
