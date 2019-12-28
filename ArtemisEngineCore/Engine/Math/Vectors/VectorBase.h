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
	class VectorBase;

	template<class T, unsigned int dimensions>
	class VectorImplementor : public IDebugStringReturner
	{
	public:
		// Returns the dot product of two vectors.
		// Value returned for normalized vector is in the interval [-1; 1]
		static double GetDotProduct(const VectorBase<T, dimensions>& a, const VectorBase<T, dimensions>& b)
		{
			T value = 0;

			for (int i = 0; i < dimensions; i++)
				value += a[i] * b[i];

			return value;
		}

		// Returns the angle between two vectors.
		// This is the unsigned angle, and will always be less than 180.
		static double GetAngle(const VectorBase<T, dimensions>& a, const VectorBase<T, dimensions>& b)
		{
			double dotProduct = GetDotProduct(a, b);
			double aMagnitude = a.GetMagnitude();
			double bMagnitude = b.GetMagnitude();

			double magnitudeProduct = aMagnitude * bMagnitude;

			double quotient = dotProduct / magnitudeProduct;

			double radians = acos(quotient);

			return radians * MathUtility::RadToDeg;
		}


		T operator[](int index) const
		{
			if (index >= 0 && index < dimensions)
			{
				return GetValue(index);
			}
			else
			{
				throw OutOfRangeException(GetOutOfRangeExceptionText(index));
			}
		}
		T& operator[](int index)
		{
			if (index >= 0 && index < dimensions)
			{
				return GetValue(index);
			}
			else
			{
				throw OutOfRangeException(GetOutOfRangeExceptionText(index));
			}
		}

		unsigned int GetDimensions() const
		{
			return dimensions;
		}

		virtual string ToString() const
		{
			std::stringstream stream;
			std::streamsize defaultPrecision = stream.precision();

			stream << "(";

			for (int i = 0; i < dimensions; i++)
			{
				T value = GetValue(i);

				if (MathUtility::IsPositiveInfinity(value))
				{
					stream << PositiveInfinityText;
				}
				else if (MathUtility::IsNegativeInfinity(value))
				{
					stream << NegativeInfinityText;
				}
				else if (MathUtility::IsNaN(value))
				{
					stream << NaNText;
				}
				else if (MathUtility::IsFloatingPointIntegral(value))
				{
					stream << std::fixed << std::setprecision(1) << value;
				}
				else
				{
					stream << std::defaultfloat << std::setprecision(defaultPrecision) << value;
				}

				if (i < dimensions - 1)
					stream << ", ";
			}

			stream << ")";

			return stream.str();
		}

		// Returns squared length of vector.
		T GetSqrMagnitude() const
		{
			T value = 0;

			for (unsigned int i = 0; i < dimensions; i++)
				value += GetValue(i) * GetValue(i);

			return value;
		}

		// Returns length of vector.
		T GetMagnitude() const
		{
			return std::sqrt(GetSqrMagnitude());
		}

		// Returns a unit vector
		VectorBase<T, dimensions> GetNormalized() const
		{
			VectorBase<T, dimensions> toReturn;

			T length = GetMagnitude();

			if (length == 0)
				throw DivideByZeroException("Unable to get unit vector of vector with length 0");

			for (int i = 0; i < dimensions; i++)
				toReturn[i] = GetValue(i) / length;

			return toReturn;
		}

	protected:
		static string GetOutOfRangeExceptionText(int index)
		{
			return "Attempted to access vector member using index [" + std::to_string(index) + "], but it is out of range." +
				+"\nValid indexes are >= 0 and < " + std::to_string(dimensions);
		}

	private:
		virtual T& GetValue(int index) = 0;
		virtual T GetValue(int index) const = 0;

		inline static const string PositiveInfinityText = "PositiveInfinity";
		inline static const string NegativeInfinityText = "NegativeInfinity";
		inline static const string NaNText = "NaN";
	};


	template<class T, unsigned int dimensions>
	class VectorBase : public VectorImplementor<T, dimensions>
	{
	public:
		T values[dimensions] = {};

		VectorBase<T, dimensions>()
		{
			for (unsigned int i = 0; i < dimensions; i++)
			{
				values[i] = 0;
			}
		}

	private:
		T& GetValue(int index) override
		{
			return values[index];
		}
		T GetValue(int index) const override
		{
			return values[index];
		}
	};


	template<class T>
	class VectorBase<T, 2> : public VectorImplementor<T, 2>
	{
	public:
		T x;
		T y;
				
		VectorBase(T x, T y)
		{
			this->x = x;
			this->y = y;
		}

		VectorBase() = default;
		~VectorBase() = default;
		VectorBase(const VectorBase& copy) = default;
		VectorBase(VectorBase&& move) = default;
		VectorBase& operator=(VectorBase& copy) = default;
		VectorBase& operator=(VectorBase&& move) = default;

	private:
		T& GetValue(int index) override
		{
			if (index == 0)
			{
				return x;
			}
			else if (index == 1)
			{
				return y;
			}
			else
			{
				throw OutOfRangeException(GetOutOfRangeExceptionText(index));
			}
		}
		T GetValue(int index) const override
		{
			if (index == 0)
			{
				return x;
			}
			else if (index == 1)
			{
				return y;
			}
			else
			{
				throw OutOfRangeException(GetOutOfRangeExceptionText(index));
			}
		}
	};

	template<class T>
	class VectorBase<T, 3> : public VectorImplementor<T, 3>
	{
	public:
		T x;
		T y;
		T z;

		// Returns cross product of two vectors
		static VectorBase GetCrossProduct(const VectorBase& a, const VectorBase& b)
		{
			return VectorWrapper<T>(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x);
		}

		VectorBase()
		{
			x = 0;
			y = 0;
			z = 0;
		}
		VectorBase(T x, T y)
		{
			this->x = x;
			this->y = y;
			this->z = 0;
		}
		VectorBase(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

	private:
		T& GetValue(int index) override
		{
			if (index == 0)
			{
				return x;
			}
			else if (index == 1)
			{
				return y;
			}
			else if (index == 2)
			{
				return z;
			}
			else
			{
				throw OutOfRangeException(GetOutOfRangeExceptionText(index));
			}
		}
		T GetValue(int index) const override
		{
			if (index == 0)
			{
				return x;
			}
			else if (index == 1)
			{
				return y;
			}
			else if (index == 2)
			{
				return z;
			}
			else
			{
				throw OutOfRangeException(GetOutOfRangeExceptionText(index));
			}
		}
	};

	template<class T>
	class VectorBase<T, 4> : public VectorImplementor<T, 4>
	{
	public:
		T x;
		T y;
		T z;
		T w;

		VectorBase()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}
		VectorBase(T x, T y)
		{
			this->x = x;
			this->y = y;
			this->z = 0;
			this->w = 0;
		}
		VectorBase(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = 0;
		}
		VectorBase(T x, T y, T z, T w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

	private:
		T& GetValue(int index) override
		{
			if (index == 0)
			{
				return x;
			}
			else if (index == 1)
			{
				return y;
			}
			else if (index == 2)
			{
				return z;
			}
			else if (index == 3)
			{
				return w;
			}
			else
			{
				throw OutOfRangeException(GetOutOfRangeExceptionText(index));
			}
		}
		T GetValue(int index) const override
		{
			if (index == 0)
			{
				return x;
			}
			else if (index == 1)
			{
				return y;
			}
			else if (index == 2)
			{
				return z;
			}
			else if (index == 3)
			{
				return w;
			}
			else
			{
				throw OutOfRangeException(GetOutOfRangeExceptionText(index));
			}
		}
	};


	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> operator+(const VectorBase<T, dimensions> a, const VectorBase<T, dimensions> b)
	{
		VectorBase<T, dimensions> c;

		for (unsigned int i = 0; i < dimensions; i++)
		{
			c[i] = a[i] + b[i];
		}

		return c;
	}
	template<class T, unsigned int dimensions>
	void operator+=(VectorBase<T, dimensions>& a, const VectorBase<T, dimensions> b)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			a[i] += b[i];
		}
	}
	template<class T, unsigned int dimensions, class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
	VectorBase<T, dimensions> operator+(const VectorBase<T, dimensions> vector, const TValue value)
	{
		VectorBase<T, dimensions> toReturn;

		for (unsigned int i = 0; i < dimensions; i++)
		{
			toReturn[i] = vector[i] + value;
		}

		return toReturn;
	}
	template<class T, unsigned int dimensions, class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
	void operator+=(VectorBase<T, dimensions>& vector, const TValue value)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			vector[i] += value;
		}
	}

	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> operator-(const VectorBase<T, dimensions> a, const VectorBase<T, dimensions> b)
	{
		VectorBase<T, dimensions> c;

		for (unsigned int i = 0; i < dimensions; i++)
		{
			c[i] = a[i] - b[i];
		}

		return c;
	}
	template<class T, unsigned int dimensions>
	void operator-=(VectorBase<T, dimensions>& a, const VectorBase<T, dimensions> b)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			a[i] -= b[i];
		}
	}
	template<class T, unsigned int dimensions, class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
	VectorBase<T, dimensions> operator-(const VectorBase<T, dimensions> vector, const TValue value)
	{
		VectorBase<T, dimensions> toReturn;

		for (unsigned int i = 0; i < dimensions; i++)
		{
			toReturn[i] = vector[i] - value;
		}

		return toReturn;
	}
	template<class T, unsigned int dimensions, class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
	void operator-=(VectorBase<T, dimensions>& vector, const TValue value)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			vector[i] -= value;
		}
	}

	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> operator*(const VectorBase<T, dimensions> a, const VectorBase<T, dimensions> b)
	{
		VectorBase<T, dimensions> c;

		for (unsigned int i = 0; i < dimensions; i++)
		{
			c[i] = a[i] * b[i];
		}

		return c;
	}
	template<class T, unsigned int dimensions>
	void operator*=(VectorBase<T, dimensions>& a, const VectorBase<T, dimensions> b)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			a[i] *= b[i];
		}
	}
	template<class T, unsigned int dimensions, class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
	VectorBase<T, dimensions> operator*(const VectorBase<T, dimensions> vector, const TValue value)
	{
		VectorBase<T, dimensions> toReturn;

		for (unsigned int i = 0; i < dimensions; i++)
		{
			toReturn[i] = vector[i] * value;
		}

		return toReturn;
	}
	template<class T, unsigned int dimensions, class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
	void operator*=(VectorBase<T, dimensions>& vector, const TValue value)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			vector[i] *= value;
		}
	}

	template<class T, unsigned int dimensions>
	VectorBase<T, dimensions> operator/(const VectorBase<T, dimensions> a, const VectorBase<T, dimensions> b)
	{
		VectorBase<T, dimensions> c;

		for (unsigned int i = 0; i < dimensions; i++)
		{
			c[i] = a[i] / b[i];
		}

		return c;
	}
	template<class T, unsigned int dimensions>
	void operator/=(VectorBase<T, dimensions>& a, const VectorBase<T, dimensions> b)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			a[i] /= b[i];
		}
	}
	template<class T, unsigned int dimensions, class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
	VectorBase<T, dimensions> operator/(const VectorBase<T, dimensions> vector, const TValue value)
	{
		VectorBase<T, dimensions> toReturn;

		for (unsigned int i = 0; i < dimensions; i++)
		{
			toReturn[i] = vector[i] / value;
		}

		return toReturn;
	}
	template<class T, unsigned int dimensions, class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
	void operator/=(VectorBase<T, dimensions>& vector, const TValue value)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			vector[i] /= value;
		}
	}
}