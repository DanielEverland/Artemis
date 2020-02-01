#include "Quaternion.h"

using ArtemisEngine::Quaternion;

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