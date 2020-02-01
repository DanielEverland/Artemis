#pragma once

#include "Math/Vectors/Vector3Base.h"

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
			this->x = copy.x;
			this->y = copy.y;
			this->z = copy.z;

			return *this;
		}
		IntVector3& operator=(Vector3Base<int>&& move)
		{
			this->x = move.x;
			this->y = move.y;
			this->z = move.z;

			move.x = 0;
			move.y = 0;
			move.z = 0;

			return *this;
		}
	};
}