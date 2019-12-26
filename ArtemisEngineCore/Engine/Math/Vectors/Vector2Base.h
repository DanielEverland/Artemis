#pragma once

#include <cmath>

#include "Exceptions/InvalidArgumentException.h"
#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	class Vector2Base : public VectorBase<T, 2>
	{
	public:
		Vector2Base()
		{
		}
		Vector2Base(T x, T y)
		{
			SetX(x);
			SetY(y);
		}
		Vector2Base(const VectorBase<T, 2>& copy)
		{
			SetX(copy[0]);
			SetY(copy[1]);
		}

		T GetX() const
		{
			return (*this)[0];
		}
		T GetY() const
		{
			return (*this)[1];
		}

		void SetX(const T value)
		{
			(*this)[0] = value;
		}
		void SetY(const T value)
		{
			(*this)[1] = value;
		}
	};
}