#pragma once

#include <algorithm>
#include <cmath>
#include <sstream>

#include <Exceptions/OutOfRangeException.h>
#include <Exceptions/DivideByZeroException.h>
#include <Debug/IDebugStringReturner.h>

using ArtemisEngine::Debug::IDebugStringReturner;

namespace ArtemisEngine::Math::Vectors
{
	template<class T, unsigned int dimensions>
	struct VectorBase : public IDebugStringReturner
	{
	public:
		T operator[](int index) const;
		T& operator[](int index);

		// Returns the dot product of two vectors.
		// Value can be between -1 and 1
		static T GetDotProduct(VectorBase& a, VectorBase& b);

		// Returns squared length of vector.
		T GetSqrMagnitude() const;

		// Returns length of vector.
		T GetMagnitude() const;

		// Returns a unit vector
		VectorBase Normalized() const;

		template<class TValue>
		VectorBase operator+(TValue value);
		VectorBase operator+(VectorBase& vector);

		template<class TValue>
		VectorBase operator-(TValue value);
		VectorBase operator-(VectorBase& vector);

		template<class TValue>
		VectorBase operator*(TValue value);
		VectorBase operator*(VectorBase& vector);

		template<class TValue>
		VectorBase operator/(TValue value);
		VectorBase operator/(VectorBase& vector);

		virtual string ToString() const override;
		
	private:
		bool IsIndexValid(int index) const;
		string GetOutOfRangeExceptionText(int index) const;

		T values[dimensions] = {};
	};



	template<class T, unsigned int dimensions>
	inline T VectorBase<T, dimensions>::operator[](int index) const
	{
		if (IsIndexValid(index))
		{
			return values[index];
		}
		else
		{
			throw OutOfRangeException(GetOutOfRangeExceptionText(index));
		}
	}

	template<class T, unsigned int dimensions>
	inline T& VectorBase<T, dimensions>::operator[](int index)
	{
		if (IsIndexValid(index))
		{
			return values[index];
		}
		else
		{
			throw OutOfRangeException(GetOutOfRangeExceptionText(index));
		}
	}

	template<class T, unsigned int dimensions>
	inline static T VectorBase<T, dimensions>::GetDotProduct(VectorBase& a, VectorBase& b)
	{
		T value;

		for (int i = 0; i < dimensions; i++)
			value = a[i] * b[i];

		return std::clamp(value, -1, 1);
	}

	template<class T, unsigned int dimensions>
	inline T VectorBase<T, dimensions>::GetSqrMagnitude() const
	{
		return GetDotProduct(this, this);
	}

	template<class T, unsigned int dimensions>
	T VectorBase<T, dimensions>::GetMagnitude() const
	{
		return std::sqrt(GetSqrMagnitude());
	}

	template<class T, unsigned int dimensions>
	inline VectorBase<T, dimensions> VectorBase<T, dimensions>::Normalized() const
	{
		T length = GetMagnitude();

		if (length == 0)
			throw DivideByZeroException("Unable to get unit vector of vector with length 0");

		VectorBase newVector();

		for (int i = 0; i < dimensions; i++)
			newVector[i] = this[i] / length;

		return newVector;
	}

	template<class T, unsigned int dimensions>
	template<class TValue>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator+(TValue value)
	{
		for (int i = 0; i < dimensions; i++)
			this[i] + value;

		return this;
	}
	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator+(VectorBase<T, dimensions>& vector)
	{
		for (int i = 0; i < dimensions; i++)
			this[i] + vector[i];

		return this;
	}

	template<class T, unsigned int dimensions>
	template<class TValue>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator-(TValue value)
	{
		for (int i = 0; i < dimensions; i++)
			this[i] - value;

		return this;
	}
	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator-(VectorBase<T, dimensions>& vector)
	{
		for (int i = 0; i < dimensions; i++)
			this[i] - vector[i];

		return this;
	}

	template<class T, unsigned int dimensions>
	template<class TValue>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator*(TValue value)
	{
		for (int i = 0; i < dimensions; i++)
			this[i] * value;

		return this;
	}
	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator*(VectorBase<T, dimensions>& vector)
	{
		for (int i = 0; i < dimensions; i++)
			this[i] * vector[i];

		return this;
	}

	template<class T, unsigned int dimensions>
	template<class TValue>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator/(TValue value)
	{
		for (int i = 0; i < dimensions; i++)
			this[i] / value;

		return this;
	}
	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator/(VectorBase<T, dimensions>& vector)
	{
		for (int i = 0; i < dimensions; i++)
			this[i] / vector[i];

		return this;
	}

	template<class T, unsigned int dimensions>
	bool VectorBase<T, dimensions>::IsIndexValid(int index) const
	{
		return index >= 0 && index < dimensions;
	}

	template<class T, unsigned int dimensions>
	inline string VectorBase<T, dimensions>::GetOutOfRangeExceptionText(int index) const
	{
		return "Attempted to access vector member using index [" + std::to_string(index) + "], but it is out of range." +
			+"\nValid indexes are >= 0 and < " + std::to_string(dimensions);
	}

	template<class T, unsigned int dimensions>
	inline string VectorBase<T, dimensions>::ToString() const
	{
		std::stringstream stream;

		stream << "(";

		for (unsigned int i = 0; i < dimensions; i++)
		{
			stream << values[i];

			if (i < dimensions - 1)
				stream << ", ";
		}

		stream << ")";

		return stream.str();
	}
}