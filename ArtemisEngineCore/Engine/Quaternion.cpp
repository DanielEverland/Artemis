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
Quaternion Quaternion::GetConjugate() const
{
	return Quaternion(-this->X, -this->Y, -this->Z, this->W);
}

double Quaternion::Magnitude() const
{
	double x = Math::Square(X);
	double y = Math::Square(Y);
	double z = Math::Square(Z);
	double w = Math::Square(W);

	double sum = x + y + z + w;

	double magnitude = Math::SquareRoot(sum);

	return magnitude;
}

Vector3 Quaternion::operator*(const Vector3& point) const
{
	double x = X * 2;
	double y = Y * 2;
	double z = Z * 2;
	double xx = X * x;
	double yy = Y * y;
	double zz = Z * z;
	double xy = X * y;
	double xz = X * z;
	double yz = Y * z;
	double wx = W * x;
	double wy = W * y;
	double wz = W * z;

	Vector3 res;
	res.x = (1.0 - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
	res.y = (xy + wz) * point.x + (1.0 - (xx + zz)) * point.y + (yz - wx) * point.z;
	res.z = (xz - wy) * point.x + (yz + wx) * point.y + (1.0 - (xx + yy)) * point.z;
	return res;
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
Quaternion Quaternion::operator*(double scalar) const
{
	return Quaternion(
		this->X * scalar,
		this->Y * scalar,
		this->Z * scalar,
		this->W * scalar);
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

	euler.x = Math::ArcTan2(2 * Y * W - 2 * X * Z, 1 - 2 * Math::Square(Y) - 2 * Math::Square(Z));
	euler.y = Math::ArcSin(2 * X * Y + 2 * Z * W);
	euler.z = Math::ArcTan2(2 * X * W - 2 * Y * Z, 1 - 2 * Math::Square(X) - 2 * Math::Square(Z));


	euler.x *= Math::RadToDeg;
	euler.y *= Math::RadToDeg;
	euler.z *= Math::RadToDeg;

	return euler;
}