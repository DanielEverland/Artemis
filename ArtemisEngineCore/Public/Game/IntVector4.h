#pragma once

#include "Public/Maths/Vector4Base.h"

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
			this->X = copy.X;
			this->Y = copy.Y;
			this->Z = copy.Z;
			this->W = copy.W;

			return *this;
		}
		IntVector4& operator=(Vector4Base<int>&& move)
		{
			this->X = move.X;
			this->Y = move.Y;
			this->Z = move.Z;
			this->W = move.W;

			move.X = 0;
			move.Y = 0;
			move.Z = 0;
			move.W = 0;

			return *this;
		}
	};
}