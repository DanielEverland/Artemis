#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	struct Vector4Base : protected VectorBase<T, 4>
	{
	public:
		Vector4Base();
		Vector4Base(T x, T y);
		Vector4Base(T x, T y, T z);
		Vector4Base(T x, T y, T z, T w);

		T& operator[](int index) const override;

		T x;
		T y;
		T z;
		T w;
	};
}
