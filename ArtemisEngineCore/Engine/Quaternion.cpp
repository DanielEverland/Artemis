#include "Quaternion.h"
#include "Math.h"

using namespace ArtemisEngine;

Quaternion::Quaternion(Vector3 rotation)
{
	FromEuler(rotation.x, rotation.y, rotation.z);
}

Quaternion::Quaternion(double xRotation, double yRotation, double zRotation)
{
	FromEuler(xRotation, yRotation, zRotation);
}

Quaternion::Quaternion(double x, double y, double z, double w)
{
	this->X = x;
	this->Y = y;
	this->Z = z;
	this->W = w;
}

Quaternion Quaternion::GetIdentity()
{
	return Quaternion(0, 0, 0, 1);
}

bool Quaternion::operator==(const Quaternion& other) const
{
	return
		this->X == other.X &&
		this->Y == other.Y &&
		this->Z == other.Z &&
		this->W == other.W;
}
Quaternion Quaternion::operator+(const Quaternion& other) const
{
	Quaternion sum{};

	sum.X = this->X + other.X;
	sum.Y = this->Y + other.Y;
	sum.Z = this->Z + other.Z;
	sum.W = this->W + other.W;

	return sum;
}
Quaternion Quaternion::operator-(const Quaternion& other) const
{
	Quaternion difference{};

	difference.X = this->X - other.X;
	difference.Y = this->Y - other.Y;
	difference.Z = this->Z - other.Z;
	difference.W = this->W - other.W;

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
	this->X += other.X;
	this->Y += other.Y;
	this->Z += other.Z;
	this->W += other.W;
}
void Quaternion::operator-=(const Quaternion& other)
{
	this->X -= other.X;
	this->Y -= other.Y;
	this->Z -= other.Z;
	this->W -= other.W;
}
void Quaternion::operator*=(const Quaternion& other)
{
	(*this) += (*this) * other;
}
void Quaternion::FromEuler(double x, double y, double z)
{
	x *= Math::DegToRad;
	y *= Math::DegToRad;
	z *= Math::DegToRad;

	// Abbreviations for the various angular functions
	double xCos = Math::Cos(x / 2);
	double xSin = Math::Sin(x / 2);
	double yCos = Math::Cos(y / 2);
	double ySin = Math::Sin(y / 2);
	double zCos = Math::Cos(z / 2);
	double zSin = Math::Sin(z / 2);

	X = xCos * yCos * zSin - xSin * ySin * zCos;
	Y = xSin * yCos * zSin + xCos * ySin * zCos;
	Z = xSin * yCos * zCos - xCos * ySin * zSin;
	W = xCos * yCos * zCos + xSin * ySin * zSin;
}
Vector3 Quaternion::GetEulerAngles() const
{
	Vector3 angles;

	double siny_cosp = 2 * (W * Z + X * Y);
	double cosy_cosp = 1 - 2 * (Y * Y + Z * Z);
	angles.x = Math::ArcTan2(siny_cosp, cosy_cosp);


	double sinp = 2 * (W * Y - Z * X);
	if (Math::Absolute(sinp) >= 1)
		angles.y = Math::CopySign(M_PI / 2, sinp); // use 90 degrees if out of range
	else
		angles.y = Math::ArcSin(sinp);

	
	double sinr_cosp = 2 * (W * X + Y * Z);
	double cosr_cosp = 1 - 2 * (X * X + Y * Y);
	angles.z = Math::ArcTan2(sinr_cosp, cosr_cosp);

	angles.x *= Math::RadToDeg;
	angles.y *= Math::RadToDeg;
	angles.z *= Math::RadToDeg;

	return angles;
}