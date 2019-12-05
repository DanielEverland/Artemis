#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	struct Vector3Base : protected VectorBase<T, 3>
	{
	public:
		Vector3Base()
		{
		}
		Vector3Base(T x, T y)
		{
			this[0] = x;
			this[1] = y;
		}
		Vector3Base(T x, T y, T z)
		{
			this[0] = x;
			this[1] = y;
			this[2] = z;
		}

		// Returns cross product of two vectors
		static Vector3Base& GetCrossProduct(Vector3Base& a, Vector3Base& b)
		{
			return Vector3Base<T>(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x);
		}
	};
}
