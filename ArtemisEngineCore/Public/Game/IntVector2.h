#pragma once

#include "Private/Maths/Vector2Base.h"

using ArtemisEngine::Maths::Vectors::Vector2Base;

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

		IntVector2& operator=(const Vector2Base<int>& copy)
		{
			this->X = copy.X;
			this->Y = copy.Y;

			return *this;
		}
		IntVector2& operator=(Vector2Base<int>&& move)
		{
			this->X = move.X;
			this->Y = move.Y;

			move.X = 0;
			move.Y = 0;

			return *this;
		}
	};
}