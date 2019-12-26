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
			for (unsigned int i = 0; i < 4; i++)
			{
				this->values[i] = copy[i];
			}
		}
	};
}
