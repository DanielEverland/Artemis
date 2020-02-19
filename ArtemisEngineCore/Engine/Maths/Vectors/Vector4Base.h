#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Maths::Vectors
{
	template<class T>
	struct Vector4Base : public VectorBase<T, 4>
	{
	public:
		~Vector4Base() = default;
		Vector4Base() : VectorBase<T, 4>() { }
		Vector4Base(T x, T y) : VectorBase<T, 4>(x, y) { }
		Vector4Base(T x, T y, T z) : VectorBase<T, 4>(x, y, z) { }
		Vector4Base(T x, T y, T z, T w) : VectorBase<T, 4>(x, y, z, w) { }
		Vector4Base(std::initializer_list<T> arguments) : VectorBase<T, 4>(arguments) { }
		Vector4Base(const VectorBase<T, 4>& copy) : VectorBase<T, 4>(copy) { }
		Vector4Base(VectorBase<T, 4>&& move) : VectorBase<T, 4>(move) { }

		template<class TOther>
		Vector4Base(const VectorBase<TOther, 2>& other) : VectorBase<T, 4>(other) { }
		template<class TOther>
		Vector4Base(const VectorBase<TOther, 3>& other) : VectorBase<T, 4>(other) { }

		Vector4Base& operator=(VectorBase<T, 4>& copy)
		{
			this->X = copy.X;
			this->Y = copy.Y;
			this->Z = copy.Z;
			this->W = copy.W;

			return *this;
		}
		Vector4Base& operator=(VectorBase<T, 4>&& move)
		{
			this->X = move.X;
			this->Y = move.Y;
			this->Z = move.Z;
			this->W = move.W;

			move.X = 0;
			move.Y = 0;
			move.Z = 0;
			move.W = 0;

			return *this;
		}
	};
}
