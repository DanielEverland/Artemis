#pragma once

#include <algorithm>
#include <cmath>
#include <sstream>
#include <utility>

#include "Exceptions/OutOfRangeException.h"
#include "Exceptions/DivideByZeroException.h"
#include "Debugging/IDebugStringReturner.h"
#include "Engine/Math/MathUtility.h"

using ArtemisEngine::Debugging::IDebugStringReturner;

namespace ArtemisEngine::Math::Vectors
{
	template<class T, unsigned int dimensions>
	struct VectorBase : public IDebugStringReturner
	{
	public:

		T operator[](int index) const;
		T& operator[](int index);

		// Returns the algebraic dot product
		static double GetAlgebraicDotProduct(const VectorBase& a, const VectorBase& b)
		{
			T value = 0;

			for (int i = 0; i < dimensions; i++)
				value += a[i] * b[i];

			return value;
		}

		// Returns the angle between two vectors.
		// This is the unsigned angle, and will always be less than 180.
		static double GetAngle(const VectorBase& a, const VectorBase& b)
		{
			double dotProduct = GetAlgebraicDotProduct(a, b);
			double aMagnitude = a.GetMagnitude();
			double bMagnitude = b.GetMagnitude();

			double magnitudeProduct = aMagnitude * bMagnitude;

			double quotient = dotProduct / magnitudeProduct;

			double radians = acos(quotient);

			return radians * MathUtility::RadToDeg;
		}

		// Returns the dot product of two vectors.
		// Value returned for normalized vector is in the interval [-1; 1]
		static double GetDotProduct(const VectorBase& a, const VectorBase& b)
		{
			double magnitudeProduct = a.GetMagnitude() * b.GetMagnitude();
			
			double angleCosine = cos(GetAngle(a, b) * MathUtility::DegToRad);

			return magnitudeProduct * angleCosine;
		}
		
		// Returns squared length of vector.
		T GetSqrMagnitude() const;

		// Returns length of vector.
		T GetMagnitude() const;

		// Returns a unit vector
		VectorBase Normalized() const;

		template<class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
		VectorBase operator+(const TValue value) const;
		VectorBase operator+(const VectorBase& vector) const;

		template<class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
		VectorBase operator-(const TValue value) const;
		VectorBase operator-(const VectorBase& vector) const;

		template<class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
		VectorBase operator*(const TValue value) const;
		VectorBase operator*(const VectorBase& vector) const;

		template<class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
		VectorBase operator/(const TValue value) const;
		VectorBase operator/(const VectorBase& vector) const;

		virtual string ToString() const override;

	private:
		bool IsIndexValid(int index) const;
		string GetOutOfRangeExceptionText(int index) const;

		T values[dimensions] = {};
	};



	template<class T, unsigned int dimensions>
	T VectorBase<T, dimensions>::operator[](int index) const
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
	T& VectorBase<T, dimensions>::operator[](int index)
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
	T VectorBase<T, dimensions>::GetSqrMagnitude() const
	{
		T value = 0;

		for (unsigned int i = 0; i < dimensions; i++)
			value += values[i] * values[i];

		return value;
	}

	template<class T, unsigned int dimensions>
	T VectorBase<T, dimensions>::GetMagnitude() const
	{
		return std::sqrt(GetSqrMagnitude());
	}

	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::Normalized() const
	{
		T length = GetMagnitude();

		if (length == 0)
			throw DivideByZeroException("Unable to get unit vector of vector with length 0");

		VectorBase<T, dimensions> newVector;

		for (int i = 0; i < dimensions; i++)
			newVector[i] = values[i] / length;

		return newVector;
	}

	template<class T, unsigned int dimensions>
	template<class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type*>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator+(const TValue value) const
	{
		VectorBase<T, dimensions> toReturn(*this);

		for (int i = 0; i < dimensions; i++)
			toReturn[i] += value;

		return toReturn;
	}
	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator+(const VectorBase<T, dimensions>& vector) const
	{
		VectorBase<T, dimensions> toReturn(*this);

		for (int i = 0; i < dimensions; i++)
			toReturn[i] += vector[i];

		return toReturn;
	}
	template<class T, unsigned int dimensions>
	template<class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type*>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator-(const TValue value) const
	{
		VectorBase<T, dimensions> toReturn(*this);

		for (int i = 0; i < dimensions; i++)
			toReturn[i] -= value;

		return toReturn;
	}
	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator-(const VectorBase<T, dimensions>& vector) const
	{
		VectorBase<T, dimensions> toReturn(*this);

		for (int i = 0; i < dimensions; i++)
			toReturn[i] -= vector[i];

		return toReturn;
	}
	template<class T, unsigned int dimensions>
	template<class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type*>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator*(const TValue value) const
	{
		VectorBase<T, dimensions> toReturn(*this);

		for (int i = 0; i < dimensions; i++)
			toReturn[i] *= value;

		return toReturn;
	}
	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator*(const VectorBase<T, dimensions>& vector) const
	{
		VectorBase<T, dimensions> toReturn(*this);

		for (int i = 0; i < dimensions; i++)
			toReturn[i] *= vector[i];

		return toReturn;
	}
	template<class T, unsigned int dimensions>
	template<class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type*>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator/(const TValue value) const
	{
		VectorBase<T, dimensions> toReturn(*this);

		for (int i = 0; i < dimensions; i++)
			toReturn[i] /= value;

		return toReturn;
	}
	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> VectorBase<T, dimensions>::operator/(const VectorBase<T, dimensions>& vector) const
	{
		VectorBase<T, dimensions> toReturn(*this);

		for (int i = 0; i < dimensions; i++)
			toReturn[i] /= vector[i];

		return toReturn;
	}

	template<class T, unsigned int dimensions>
	bool VectorBase<T, dimensions>::IsIndexValid(int index) const
	{
		return index >= 0 && index < dimensions;
	}

	template<class T, unsigned int dimensions>
	string VectorBase<T, dimensions>::GetOutOfRangeExceptionText(int index) const
	{
		return "Attempted to access vector member using index [" + std::to_string(index) + "], but it is out of range." +
			+"\nValid indexes are >= 0 and < " + std::to_string(dimensions);
	}

	template<class T, unsigned int dimensions>
	string VectorBase<T, dimensions>::ToString() const
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