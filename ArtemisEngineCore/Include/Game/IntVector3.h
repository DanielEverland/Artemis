#pragma once

#include "Include/Maths/Vector3Base.h"

using ArtemisEngine::Maths::Vectors::Vector3Base;

namespace ArtemisEngine
{
	class IntVector3 : public Vector3Base<int>
	{
	public:
		~IntVector3() = default;
		IntVector3() : Vector3Base<int>() { }
		IntVector3(int x, int y) : Vector3Base<int>(x, y) { }
		IntVector3(int x, int y, int z) : Vector3Base<int>(x, y, z) { }
		IntVector3(const VectorBase& copy) : Vector3Base<int>(copy) { }
		IntVector3(VectorBase&& move) : Vector3Base<int>(move) { }

		IntVector3& operator=(const Vector3Base<int>& copy)
		{
			this->X = copy.X;
			this->Y = copy.Y;
			this->Z = copy.Z;

			return *this;
		}
		IntVector3& operator=(Vector3Base<int>&& move)
		{
			this->X = move.X;
			this->Y = move.Y;
			this->Z = move.Z;

			move.X = 0;
			move.Y = 0;
			move.Z = 0;

			return *this;
		}
	};
}