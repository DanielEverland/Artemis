#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	class Vector3Base : public VectorWrapper<T, 3>
	{
		using VectorWrapper::VectorWrapper;

	public:
		Vector3Base(const VectorWrapper<T, 3> copy)
		{
			for (unsigned int i = 0; i < 3; i++)
			{
				this->values[i] = copy[i];
			}
		}

		// Returns cross product of two vectors
		static Vector3Base GetCrossProduct(const Vector3Base& a, const Vector3Base& b)
		{
			return Vector3Base<T>(
				a.GetY() * b.GetZ() - a.GetZ() * b.GetY(),
				a.GetZ() * b.GetX() - a.GetX() * b.GetZ(),
				a.GetX() * b.GetY() - a.GetY() * b.GetX());
		}
	};
}
