#pragma once

#include "Engine/Vector3.h"

namespace ArtemisEngine
{
	class Quaternion
	{
	public:

		Quaternion operator+(const Quaternion& other) const;
		Quaternion operator-(const Quaternion& other) const;
		Quaternion operator*(const Quaternion& other) const;
		void operator+=(const Quaternion& other);
		void operator-=(const Quaternion& other);
		void operator*=(const Quaternion& other);
		bool operator==(const Quaternion& other) const;

	private:
		
		Vector3 imaginary;
		double real;
	};
}