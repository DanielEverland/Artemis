#pragma once

#include "Engine/Math/Vectors/Vector4Base.h"

using ArtemisEngine::Math::Vectors::Vector4Base;

namespace ArtemisEngine
{
	class IntVector4 : public Vector4Base<int>
	{
	public:
		~IntVector4() = default;
		IntVector4() : Vector4Base<int>() { }
		IntVector4(int x, int y) : Vector4Base<int>(x, y) { }
		IntVector4(int x, int y, int z) : Vector4Base<int>(x, y, z) { }
		IntVector4(int x, int y, int z, int w) : Vector4Base<int>(x, y, z, w) { }
		IntVector4(const VectorBase& copy) : Vector4Base<int>(copy) { }
		IntVector4(VectorBase&& move) : Vector4Base<int>(move) { }

		IntVector4& operator=(VectorBase& copy)
		{
			this->x = copy.x;
			this->y = copy.y;

			return *this;
		}
		IntVector4& operator=(VectorBase&& move)
		{
			this->x = move.x;
			this->y = move.y;

			move.x = 0;
			move.y = 0;

			return *this;
		}
	};
}