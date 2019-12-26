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
			SetX(x);
			SetY(y);
			SetZ(0);
			SetW(0);
		}
		Vector4Base(T x, T y, T z)
		{
			SetX(x);
			SetY(y);
			SetZ(z);
			SetW(0);
		}
		Vector4Base(T x, T y, T z, T w)
		{
			SetX(x);
			SetY(y);
			SetZ(z);
			SetW(w);
		}
		Vector4Base(const VectorBase<T, 4> other)
		{
			SetX(other[0]);
			SetY(other[1]);
			SetZ(other[2]);
			SetW(other[3]);
		}

		T GetX() const
		{
			return (*this)[0];
		}
		T GetY() const
		{
			return (*this)[1];
		}
		T GetZ() const
		{
			return (*this)[2];
		}
		T GetW() const
		{
			return (*this)[3];
		}

		void SetX(const T value)
		{
			(*this)[0] = value;
		}
		void SetY(const T value)
		{
			(*this)[1] = value;
		}
		void SetZ(const T value)
		{
			(*this)[2] = value;
		}
		void SetW(const T value)
		{
			(*this)[3] = value;
		}
	};
}
