#pragma once

#include "VectorBase.h"

namespace ArtemisEngine
{
	namespace Math
	{
		template<class T>
		struct Vector3Base : VectorBase<T, 3>
		{
		public:
			Vector3Base();
			Vector3Base(T x, T y);
			Vector3Base(T x, T y, T z);

			T& operator[](int index) const override;

			T x;
			T y;
			T z;

			// Returns cross product of two vectors
			static Vector3Base& CrossProduct(Vector3Base& a, Vector3Base& b);
		};
	}
}
