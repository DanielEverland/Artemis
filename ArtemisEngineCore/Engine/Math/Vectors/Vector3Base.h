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
			this->x = copy.x;
			this->y = copy.y;
			this->z = copy.z;
		}
	};
}
