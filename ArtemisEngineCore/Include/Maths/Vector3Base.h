#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Maths::Vectors
{
	template<class T>
	struct Vector3Base : public VectorBase<T, 3>
	{
	public:
		~Vector3Base() = default;
		Vector3Base() : VectorBase<T, 3>() { }
		Vector3Base(T x, T y) : VectorBase<T, 3>(x, y) { }
		Vector3Base(T x, T y, T z) : VectorBase<T, 3>(x, y, z) { }
		Vector3Base(std::initializer_list<T> arguments) : VectorBase<T, 3>(arguments) { }
		Vector3Base(const VectorBase<T, 3>& copy) : VectorBase<T, 3>(copy) { }
		Vector3Base(VectorBase<T, 3>&& move) : VectorBase<T, 3>(move) { }

		template<class TOther>
		Vector3Base(const VectorBase<TOther, 2>& other) : VectorBase<T, 3>(other) { }

		Vector3Base& operator=(VectorBase<T, 3>& copy)
		{
			this->X = copy.X;
			this->Y = copy.Y;
			this->Z = copy.Z;

			return *this;
		}
		Vector3Base& operator=(VectorBase<T, 3>&& move)
		{
			this->X = move.X;
			this->Y = move.Y;
			this->Z = move.Z;

			move.X = 0;
			move.Y = 0;
			move.Z = 0;

			return *this;
		}
	};
}
