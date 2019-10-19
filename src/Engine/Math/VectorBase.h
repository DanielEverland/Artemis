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

			// Returns squared length of vector.
			T& SqrMagnitude() const;

			// Returns length of vector.
			T& Magnitude() const;

			// Returns a unit vector
			VectorBase& Normalized() const;

			// Returns the dot product of two vectors.
			// Value can be between -1 and 1
			static T& DotProduct(VectorBase& a, VectorBase& b);
		};
	}	
}