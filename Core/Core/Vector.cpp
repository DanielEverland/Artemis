#include <sstream>
#include <cmath>

#include "Vector.h"

Vector::Vector() : X(0.0), Y(0.0)
{
}

Vector::Vector(double x, double y) : X(x), Y(y)
{
}

std::string Vector::ToString() const
{
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "(" << X << ", " << Y << ")";
	return stream.str();
}

Vector Vector::operator*(const Vector& other)
{
	return Vector(X * other.X, Y * other.Y);
}

Vector Vector::operator+(const Vector& other)
{
	return Vector(X + other.X, Y + other.Y);
}

bool Vector::SameValue(double a, double b)
{
	return fabs(a - b) < DBL_EPSILON;
}
