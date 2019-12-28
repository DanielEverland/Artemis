#pragma once

#include "Math/Vectors/Vector2Base.h"

using ArtemisEngine::Math::Vectors::Vector2Base;

namespace ArtemisEngine
{
	class IntVector2 : public Vector2Base<int>
	{
	public:
		~IntVector2() = default;
		IntVector2() : Vector2Base<int>() { }
		IntVector2(int x, int y) : Vector2Base<int>(x, y) { }
		IntVector2(const VectorBase& copy) : Vector2Base<int>(copy) { }
		IntVector2(VectorBase&& move) : Vector2Base<int>(move) { }

		IntVector2& operator=(IntVector2& copy)
		{
			this->x = copy.x;
			this->y = copy.y;

			return *this;
		}
		IntVector2& operator=(IntVector2&& move)
		{
			this->x = move.x;
			this->y = move.y;

			move.x = 0;
			move.y = 0;

			return *this;
		}
	};
}