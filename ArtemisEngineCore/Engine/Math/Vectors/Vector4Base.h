#pragma once

#include "VectorBase.h"

namespace ArtemisEngine::Math::Vectors
{
	template<class T>
	class Vector4Base : public VectorWrapper<T, 4>
	{
		using VectorWrapper::VectorWrapper;

	public:
		Vector4Base(const VectorWrapper<T, 4> copy)
		{
			this->x = copy.x;
			this->y = copy.y;
			this->z = copy.z;
			this->w = copy.w;
		}
	};
}
