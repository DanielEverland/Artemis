#include "Quaternion.h"

using ArtemisEngine::Quaternion;

Quaternion::Quaternion(double xRotation, double yRotation, double zRotation)
{
	this->imaginary = Vector3(xRotation, yRotation, zRotation);
	this->real = 0;
}

Quaternion::Quaternion(const Vector3& rotation)
{
	this->imaginary = rotation;
	this->real = 0;
}

Quaternion::Quaternion(double x, double y, double z, double w)
{
	this->imaginary = Vector3(x, y, z);
	this->real = w;
}

Quaternion Quaternion::GetIdentity()
{
	return Quaternion(0, 0, 0, 1);
}

bool Quaternion::operator==(const Quaternion& other) const
{
	return this->imaginary == other.imaginary && this->real == other.real;
}
Quaternion Quaternion::operator+(const Quaternion& other) const
{
	Quaternion sum{};

	sum.imaginary = this->imaginary + other.imaginary;
	sum.real = this->real + other.real;

	return sum;
}
Quaternion Quaternion::operator-(const Quaternion& other) const
{
	Quaternion difference{};

	difference.imaginary = this->imaginary - other.imaginary;
	difference.real = this->real - other.real;

	return difference;
}
Quaternion Quaternion::operator*(const Quaternion& other) const
{
	Quaternion product{};

	product.imaginary =
		this->real * other.imaginary + other.real * this->imaginary
		+ Vector3::GetCrossProduct(this->imaginary, other.imaginary);

	product.real = this->real * other.real - Vector3::GetDotProduct(this->imaginary, other.imaginary);

	return product;
}
void Quaternion::operator+=(const Quaternion& other)
{
	this->imaginary += other.imaginary;
	this->real += other.real;
}
void Quaternion::operator-=(const Quaternion& other)
{
	this->imaginary -= other.imaginary;
	this->real -= other.real;
}
void Quaternion::operator*=(const Quaternion& other)
{
	(*this) += (*this) * other;
}