#pragma once

#include "Engine/Math/Vectors/Vector4Base.h"

using ArtemisEngine::Maths::Vectors::Vector4Base;

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

		IntVector4& operator=(const Vector4Base<int>& copy)
		{
			this->x = copy.x;
			this->y = copy.y;
			this->z = copy.z;
			this->w = copy.w;

			return *this;
		}
		IntVector4& operator=(Vector4Base<int>&& move)
		{
			this->x = move.x;
			this->y = move.y;
			this->z = move.z;
			this->w = move.w;

			move.x = 0;
			move.y = 0;
			move.z = 0;
			move.w = 0;

			return *this;
		}
	};
}