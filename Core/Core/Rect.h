#pragma once

#include <string>

#include "Vector.h"
#include "../../SDL/include/SDL_rect.h"

struct Rect
{
public:
	Vector Position;
	Vector Size;

	[[nodiscard]] std::string ToString() const;

	operator SDL_Rect() const;

	friend bool operator==(const Rect& lhs, const Rect& rhs)
	{
		return lhs.Position == rhs.Position
			&& lhs.Size == rhs.Size;
	}

	friend bool operator!=(const Rect& lhs, const Rect& rhs)
	{
		return !(lhs == rhs);
	}

	friend std::ostream& operator<<(std::ostream& os, const Rect& obj)
	{
		return os << obj.ToString();
	}
};
