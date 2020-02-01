#include "Quaternion.h"
#include "Math.h"

using namespace ArtemisEngine;

Quaternion::Quaternion(double xRotation, double yRotation, double zRotation)
{
	FromEuler(xRotation, yRotation, zRotation);
}

Quaternion::Quaternion(double x, double y, double z, double w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion Quaternion::GetIdentity()
{
	return Quaternion(0, 0, 0, 1);
}

bool Quaternion::operator==(const Quaternion& other) const
{
	return
		this->x == other.x &&
		this->y == other.y &&
		this->z == other.z &&
		this->w == other.w;
}
Quaternion Quaternion::operator+(const Quaternion& other) const
{
	Quaternion sum{};

	sum.x = this->x + other.x;
	sum.y = this->y + other.y;
	sum.z = this->z + other.z;
	sum.w = this->w + other.w;

	return sum;
}
Quaternion Quaternion::operator-(const Quaternion& other) const
{
	Quaternion difference{};

	difference.x = this->x - other.x;
	difference.y = this->y - other.y;
	difference.z = this->z - other.z;
	difference.w = this->w - other.w;

	return difference;
}
Quaternion Quaternion::operator*(const Quaternion& other) const
{
	Quaternion product{};

	static_assert(true, "Not implemented");

	return product;
}
void Quaternion::operator+=(const Quaternion& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;
}
void Quaternion::operator-=(const Quaternion& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	this->w -= other.w;
}
void Quaternion::operator*=(const Quaternion& other)
{
	(*this) += (*this) * other;
}
void Quaternion::FromEuler(double x, double y, double z)
{
	double xCos = Math::Cos(x / 2);
	double xSin = Math::Sin(x / 2);
	double yCos = Math::Cos(y / 2);
	double ySin = Math::Sin(y / 2);
	double zCos = Math::Cos(z / 2);
	double zSin = Math::Sin(z / 2);

	x = zCos * yCos * xSin - zSin * ySin * xCos;
	y = zSin * yCos * xSin + zCos * ySin * xCos;
	z = zSin * yCos * xCos - zCos * ySin * xSin;
	w =	zCos * yCos * xCos + zSin * ySin * xSin;
}