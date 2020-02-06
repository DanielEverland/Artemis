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

Quaternion Quaternion::GetNormalized() const
{
	double magnitude = Magnitude();

	return Quaternion(
		X / magnitude,
		Y / magnitude,
		Z / magnitude,
		W / magnitude);
}

double Quaternion::Magnitude() const
{
	double x = Math::Squared(X);
	double y = Math::Squared(Y);
	double z = Math::Squared(Z);
	double w = Math::Squared(W);

	double sum = x + y + z + w;

	double magnitude = Math::SquareRoot(sum);

	return magnitude;
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

	
	                                                                                                                                                                                                                                  
	product.X = X * other.W + Y * other.Z - Z * other.Y + W * other.X;
	product.Y = -X * other.Z + Y * other.W + Z * other.X + W * other.Y;
	product.Z = X * other.Y - Y * other.X + Z * other.W + W * other.Z;
	product.W = -X * other.X - Y * other.Y - Z * other.Z + W * other.W;
	
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
	(*this) = (*this) * other;
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
	
	X = xSin * ySin * zCos + xCos * yCos * zSin;
	Y = xSin * yCos * zCos + xCos * ySin * zSin;
	Z = xCos * ySin * zCos - xSin * yCos * zSin;
	W = xCos * yCos * zCos - xSin * ySin * zSin;
}
Vector3 Quaternion::GetEulerAngles() const
{
	Vector3 euler;

	euler.x = Math::ArcTan2(2 * Y * W - 2 * X * Z, 1 - 2 * Math::Squared(Y) - 2 * Math::Squared(Z));
	euler.y = Math::ArcSin(2 * X * Y + 2 * Z * W);
	euler.z = Math::ArcTan2(2 * X * W - 2 * Y * Z, 1 - 2 * Math::Squared(X) - 2 * Math::Squared(Z));


	euler.x *= Math::RadToDeg;
	euler.y *= Math::RadToDeg;
	euler.z *= Math::RadToDeg;

	return euler;
}