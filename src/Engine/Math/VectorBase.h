#pragma once

namespace ArtemisEngine
{
	namespace Math
	{
		template<class T, unsigned int dimensions>
		struct VectorBase
		{
		public:
			virtual T& operator[](int index) const = 0;

			// Returns the dot product of two vectors.
			// Value can be between -1 and 1
			static T& GetDotProduct(VectorBase& a, VectorBase& b);

			// Returns squared length of vector.
			T& GetSqrMagnitude() const;

			// Returns length of vector.
			T& GetMagnitude() const;

			// Returns a unit vector
			VectorBase& Normalized() const;

			template<class TValue>
			VectorBase& operator+(TValue value);
			VectorBase& operator+(VectorBase& vector);

			template<class TValue>
			VectorBase& operator-(TValue value);
			VectorBase& operator-(VectorBase& vector);

			template<class TValue>
			VectorBase& operator*(TValue value);
			VectorBase& operator*(VectorBase& vector);

			template<class TValue>
			VectorBase& operator/(TValue value);
			VectorBase& operator/(VectorBase& vector);
		};
	}	
}