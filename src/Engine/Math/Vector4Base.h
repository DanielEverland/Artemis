#pragma once

#include "VectorBase.h"

namespace ArtemisEngine
{
	namespace Math
	{
		template<class T>
		struct Vector4 : protected VectorBase<T, 4>
		{
		public:
			Vector4();
			Vector4(T x, T y);
			Vector4(T x, T y, T z);
			Vector4(T x, T y, T z, T w);

			T& operator[](int index) const override;

			T x;
			T y;
			T z;
			T w;
		};
	}
}
