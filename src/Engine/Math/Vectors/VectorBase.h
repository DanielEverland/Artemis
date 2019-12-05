#pragma once

#include <Exceptions/OutOfRangeException.h>
#include <Exceptions/DivideByZeroException.h>
#include <algorithm>
#include <cmath>

namespace ArtemisEngine::Math::Vectors
{
	template<class T, unsigned int dimensions>
	struct VectorBase
	{
	public:
		T operator[](int index) const
		{
			return TryGetValue(index);
		}

		T& operator[](int index)
		{
			return TryGetValue(index);
		}

		// Returns the dot product of two vectors.
		// Value can be between -1 and 1
		static T GetDotProduct(VectorBase& a, VectorBase& b)
		{
			T value;

			for (int i = 0; i < dimensions; i++)
				value = a[i] * b[i];

			return std::clamp(value, -1, 1);
		}

		// Returns squared length of vector.
		T GetSqrMagnitude() const
		{
			return GetDotProduct(this, this);
		}

		// Returns length of vector.
		T GetMagnitude() const
		{
			return std::sqrt(GetSqrMagnitude());
		}

		// Returns a unit vector
		VectorBase Normalized() const
		{
			T length = GetMagnitude();

			if (length == 0)
				throw DivideByZeroException("Unable to get unit vector of vector with length 0");

			VectorBase newVector();

			for (int i = 0; i < dimensions; i++)
				newVector[i] = this[i] / length;

			return newVector;
		}

		template<class TValue>
		VectorBase operator+(TValue value)
		{
			for (int i = 0; i < dimensions; i++)
				this[i] + value;

			return this;
		}
		VectorBase operator+(VectorBase& vector)
		{
			for (int i = 0; i < dimensions; i++)
				this[i] + vector[i];

			return this;
		}

		template<class TValue>
		VectorBase operator-(TValue value)
		{
			for (int i = 0; i < dimensions; i++)
				this[i] - value;

			return this;
		}
		VectorBase operator-(VectorBase& vector)
		{
			for (int i = 0; i < dimensions; i++)
				this[i] - vector[i];

			return this;
		}

		template<class TValue>
		VectorBase operator*(TValue value)
		{
			for (int i = 0; i < dimensions; i++)
				this[i] * value;

			return this;
		}
		VectorBase operator*(VectorBase& vector)
		{
			for (int i = 0; i < dimensions; i++)
				this[i] * vector[i];

			return this;
		}

		template<class TValue>
		VectorBase operator/(TValue value)
		{
			for (int i = 0; i < dimensions; i++)
				this[i] / value;

			return this;
		}
		VectorBase operator/(VectorBase& vector)
		{
			for (int i = 0; i < dimensions; i++)
				this[i] / vector[i];

			return this;
		}

	private:
		T& TryGetValue(int index)
		{
			if (IsIndexValid(index))
			{
				return values[index];
			}
			else
			{
				throw OutOfRangeException("Attempted to access vector member using index [" + std::to_string(index) + "], but it is out of range." +
					+"\nValid indexes are >= 0 and < " + std::to_string(dimensions));
			}
		}
		bool IsIndexValid(int index) const
		{
			return index >= 0 && index < dimensions;
		}

		

		T values[dimensions] = {};
	};
}