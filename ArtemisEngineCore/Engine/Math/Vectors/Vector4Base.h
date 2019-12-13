#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	class Vector4Base : public VectorBase<T, 4>
	{
	public:
		Vector4Base()
		{
		}
		Vector4Base(T x, T y)
		{
			(*this)[0] = x;
			(*this)[1] = y;
		}
		Vector4Base(T x, T y, T z)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
		}
		Vector4Base(T x, T y, T z, T w)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
			(*this)[3] = w;
		}
		Vector4Base(const VectorBase<T, 4> other)
		{
			(*this)[0] = other[0];
			(*this)[1] = other[1];
			(*this)[2] = other[2];
			(*this)[3] = other[3];
		}
	};
}
