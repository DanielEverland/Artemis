#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Maths::Vectors
{
	template<class T>
	class Vector3Base : public VectorBase<T, 3>
	{
	public:
		~Vector3Base() = default;
		Vector3Base() : VectorBase<T, 3>() { }
		Vector3Base(T x, T y) : VectorBase<T, 3>(x, y) { }
		Vector3Base(T x, T y, T z) : VectorBase<T, 3>(x, y, z) { }
		Vector3Base(const VectorBase<T, 3>& copy) : VectorBase<T, 3>(copy) { }
		Vector3Base(VectorBase<T, 3>&& move) : VectorBase<T, 3>(move) { }

		Vector3Base& operator=(VectorBase<T, 3>& copy)
		{
			this->x = copy.x;
			this->y = copy.y;
			this->z = copy.z;

			return *this;
		}
		Vector3Base& operator=(VectorBase<T, 3>&& move)
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
