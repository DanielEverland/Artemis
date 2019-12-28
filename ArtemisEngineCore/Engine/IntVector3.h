#pragma once

#include "Math/Vectors/Vector3Base.h"

using ArtemisEngine::Math::Vectors::Vector3Base;

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

		IntVector3& operator=(VectorBase& copy)
		{
			this->x = copy.x;
			this->y = copy.y;

			return *this;
		}
		IntVector3& operator=(VectorBase&& move)
		{
			this->x = move.x;
			this->y = move.y;

			move.x = 0;
			move.y = 0;

			return *this;
		}
	};
}