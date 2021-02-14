#pragma once

#include <string>
#include <ostream>
#include <iomanip>

struct Vector
{
public:
	double X;
	double Y;

	Vector();
	Vector(double x, double y);

	[[nodiscard]] std::string ToString() const;

	Vector operator*(const Vector& other);
	Vector operator+(const Vector& other);
	
	friend bool operator==(const Vector& lhs, const Vector& rhs)
	{
		return SameValue(lhs.X, rhs.X) && SameValue(lhs.Y, rhs.Y);
	}

	friend bool operator!=(const Vector& lhs, const Vector& rhs)
	{
		return !(lhs == rhs);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector& obj)
	{
		return os << obj.ToString();
	}

private:
	static bool SameValue(double a, double b);
};
