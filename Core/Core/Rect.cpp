#include <sstream>
#include <cmath>

#include "Rect.h"

std::string Rect::ToString() const
{
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "(x: " << Position.X << ", y: " << Position.Y << ", w: " << Size.X << ", h: " << Size.Y << ")";
	return stream.str();
}

Rect::operator SDL_Rect() const
{
	return { static_cast<int>(round(Position.X)), static_cast<int>(round(Position.Y)), static_cast<int>(round(Size.X)), static_cast<int>(round(Size.Y)) };
}
