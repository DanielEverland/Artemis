#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	class Vector3Base : public VectorBase<T, 3>
	{
	public:
		Vector3Base()
		{
		}
		Vector3Base(T x, T y)
		{
			SetX(x);
			SetY(y);
			SetZ(0);
		}
		Vector3Base(T x, T y, T z)
		{
			SetX(x);
			SetY(y);
			SetZ(z);
		}
		Vector3Base(const VectorBase<T, 3> other)
		{
			SetX(other[0]);
			SetY(other[1]);
			SetZ(other[2]);
		}

		// Returns cross product of two vectors
		static Vector3Base GetCrossProduct(const Vector3Base& a, const Vector3Base& b)
		{
			return Vector3Base<T>(
				a.GetY() * b.GetZ() - a.GetZ() * b.GetY(),
				a.GetZ() * b.GetX() - a.GetX() * b.GetZ(),
				a.GetX() * b.GetY() - a.GetY() * b.GetX());
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
	};
}
