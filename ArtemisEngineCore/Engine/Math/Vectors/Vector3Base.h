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
			(*this)[0] = x;
			(*this)[1] = y;
		}
		Vector3Base(T x, T y, T z)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
		}

		// Returns cross product of two vectors
		static Vector3Base GetCrossProduct(const Vector3Base& a, const Vector3Base& b)
		{
			return Vector3Base<T>(
				a[1] * b[2] - a[2] * b[1],
				a[2] * b[0] - a[0] * b[2],
				a[0] * b[1] - a[1] * b[0]);
		}
	};
}
