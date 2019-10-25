#pragma once

#include "VectorBase.h"

namespace ArtemisEngine
{
	namespace Math
	{
		template<class T>
		struct Vector2Base : protected VectorBase<T, 2>
		{
		public:
			Vector2Base();
			Vector2Base(T x, T y);

			T& operator[](int index) const override;

			T x;
			T y;
		};
	}
}