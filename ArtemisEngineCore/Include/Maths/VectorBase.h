#pragma once

#include <algorithm>
#include <cmath>
#include <utility>

#include "Source/Formatting/NumberFormatting.h"

#include "Include/Exceptions/OutOfRangeException.h"
#include "Include/Exceptions/DivideByZeroException.h"
#include "Include/Game/IDebugStringReturner.h"
#include "Include/Game/Math.h"

using namespace ArtemisEngine;

namespace ArtemisEngine::Maths::Vectors
{
	template<class T, unsigned int dimensions>
	struct VectorBase;

	// Vectors represent directions with a magnitude
	template<class T, unsigned int dimensions>
	struct VectorImplementor : public IDebugStringReturner
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

			double radians = Math::ArcCosine(quotient);

			return Math::RadiansToDegrees(radians);
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

		template<unsigned int newVectorDimension, typename = typename std::enable_if<(newVectorDimension < dimensions)>::type>
		operator VectorBase<T, newVectorDimension>()
		{
			VectorBase<T, newVectorDimension> toReturn;

			for (unsigned int i = 0; i < newVectorDimension; i++)
				toReturn[i] = GetValue(i);

			return toReturn;
		}

		// Returns the amount of dimensions this vector represents
		unsigned int GetDimensions() const
		{
			return dimensions;
		}

		// Returns a nicely formatted string
		virtual string ToString() const
		{
			string str = "";

			str += "(";

			for (int i = 0; i < dimensions; i++)
			{
				T value = GetValue(i);

				str += NumberFormatting::FormatGeneric(value);

				if (i < dimensions - 1)
					str += ", ";
			}

			str += ")";

			return str;
		}

		// Returns squared length of vector.
		double GetSqrMagnitude() const
		{
			T value = 0;

			for (unsigned int i = 0; i < dimensions; i++)
				value += GetValue(i) * GetValue(i);

			return value;
		}

		// Returns length of vector.
		double GetMagnitude() const
		{
			return std::sqrt(GetSqrMagnitude());
		}

		// Returns a unit vector
		VectorBase<double, dimensions> GetNormalized() const
		{
			VectorBase<double, dimensions> toReturn;

			double length = GetMagnitude();

			if (length == 0)
				throw DivideByZeroException("Unable to get unit vector of vector with length 0");

			for (int i = 0; i < dimensions; i++)
				toReturn[i] = GetValue(i) / length;

			return toReturn;
		}

	protected:
		string GetOutOfRangeExceptionText(int index) const
		{
			return "Attempted to access vector member using index [" + std::to_string(index) + "], but it is out of range." +
				+"\nValid indexes are >= 0 and < " + std::to_string(dimensions);
		}

		void InitializeFromList(std::initializer_list<T> arguments, int dimensions)
		{
			int amountOfArguments = arguments.size();
			int elementsToInitialize = min(dimensions, amountOfArguments);
			auto iter = arguments.begin();

			for (int i = 0; i < elementsToInitialize; i++)
			{
				GetValue(i) = *iter;

				iter++;
			}
		}

	private:
		virtual T& GetValue(int index) = 0;
		virtual T GetValue(int index) const = 0;
	};


	template<class T, unsigned int dimensions>
	struct VectorBase : public VectorImplementor<T, dimensions>
	{
	public:
		T values[dimensions] = {};

		template<class TOther, unsigned int otherDimensions, typename = typename std::enable_if<(otherDimensions < dimensions)>::type>
		VectorBase<T, dimensions>(const VectorBase<TOther, otherDimensions>& other)
		{
			for (unsigned int i = 0; i < otherDimensions; i++)
				values[i] = other[i];
		}

		VectorBase<T, dimensions>(std::initializer_list<T> arguments)
		{
			InitializeFromList(arguments, dimensions);
		}
		VectorBase<T, dimensions>()
		{
			for (unsigned int i = 0; i < dimensions; i++)
				values[i] = 0;
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
	struct VectorBase<T, 2> : public VectorImplementor<T, 2>
	{
	public:
		T X;
		T Y;
		
		VectorBase()
		{
			this->X = 0;
			this->Y = 0;
		}
		VectorBase(T x, T y)
		{
			this->X = x;
			this->Y = y;
		}
		VectorBase(std::initializer_list<T> arguments)
		{
			InitializeFromList(arguments, 2);
		}

	private:
		T& GetValue(int index) override
		{
			if (index == 0)
			{
				return X;
			}
			else if (index == 1)
			{
				return Y;
			}
			else
			{
				throw OutOfRangeException(this->GetOutOfRangeExceptionText(index));
			}
		}
		T GetValue(int index) const override
		{
			if (index == 0)
			{
				return X;
			}
			else if (index == 1)
			{
				return Y;
			}
			else
			{
				throw OutOfRangeException(this->GetOutOfRangeExceptionText(index));
			}
		}
	};

	template<class T>
	struct VectorBase<T, 3> : public VectorImplementor<T, 3>
	{
	public:
		T X;
		T Y;
		T Z;

		// Returns a thrid vector perpendicular to a and b
		static VectorBase GetCrossProduct(const VectorBase& a, const VectorBase& b)
		{
			return VectorBase(
				a.Y * b.Z - a.Z * b.Y,
				a.Z * b.X - a.X * b.Z,
				a.X * b.Y - a.Y * b.X);
		}

		VectorBase()
		{
			X = 0;
			Y = 0;
			Z = 0;
		}
		VectorBase(T x, T y)
		{
			this->X = x;
			this->Y = y;
			this->Z = 0;
		}
		VectorBase(T x, T y, T z)
		{
			this->X = x;
			this->Y = y;
			this->Z = z;
		}
		template<class TOther>
		VectorBase(const VectorBase<TOther, 2>& other)
		{
			this->X = other[0];
			this->Y = other[1];
			this->Z = 0;
		}
		VectorBase(std::initializer_list<T> arguments)
		{
			InitializeFromList(arguments, 3);
		}

	private:
		T& GetValue(int index) override
		{
			if (index == 0)
			{
				return X;
			}
			else if (index == 1)
			{
				return Y;
			}
			else if (index == 2)
			{
				return Z;
			}
			else
			{
				throw OutOfRangeException(this->GetOutOfRangeExceptionText(index));
			}
		}
		T GetValue(int index) const override
		{
			if (index == 0)
			{
				return X;
			}
			else if (index == 1)
			{
				return Y;
			}
			else if (index == 2)
			{
				return Z;
			}
			else
			{
				throw OutOfRangeException(this->GetOutOfRangeExceptionText(index));
			}
		}
	};

	template<class T>
	struct VectorBase<T, 4> : public VectorImplementor<T, 4>
	{
	public:
		T X;
		T Y;
		T Z;
		T W;

		VectorBase()
		{
			X = 0;
			Y = 0;
			Z = 0;
			W = 0;
		}
		VectorBase(T x, T y)
		{
			this->X = x;
			this->Y = y;
			this->Z = 0;
			this->W = 0;
		}
		VectorBase(T x, T y, T z)
		{
			this->X = x;
			this->Y = y;
			this->Z = z;
			this->W = 0;
		}
		VectorBase(T x, T y, T z, T w)
		{
			this->X = x;
			this->Y = y;
			this->Z = z;
			this->W = w;
		}
		template<class TOther>
		VectorBase(const VectorBase<TOther, 2>& other)
		{
			this->X = other[0];
			this->Y = other[1];
			this->Z = 0;
			this->W = 0;
		}
		template<class TOther>
		VectorBase(const VectorBase<TOther, 3>& other)
		{
			this->X = other[0];
			this->Y = other[1];
			this->Z = other[2];
			this->W = 0;
		}
		VectorBase(std::initializer_list<T> arguments)
		{
			InitializeFromList(arguments, 4);
		}

	private:
		T& GetValue(int index) override
		{
			if (index == 0)
			{
				return X;
			}
			else if (index == 1)
			{
				return Y;
			}
			else if (index == 2)
			{
				return Z;
			}
			else if (index == 3)
			{
				return W;
			}
			else
			{
				throw OutOfRangeException(this->GetOutOfRangeExceptionText(index));
			}
		}
		T GetValue(int index) const override
		{
			if (index == 0)
			{
				return X;
			}
			else if (index == 1)
			{
				return Y;
			}
			else if (index == 2)
			{
				return Z;
			}
			else if (index == 3)
			{
				return W;
			}
			else
			{
				throw OutOfRangeException(this->GetOutOfRangeExceptionText(index));
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
	template<class T, unsigned int dimensions, class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
	VectorBase<T, dimensions> operator*(const TValue value, const VectorBase<T, dimensions> vector)
	{
		return vector * value;
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
	void operator*=(const TValue value, VectorBase<T, dimensions>& vector)
	{
		return vector * value;
	}
	template<class T, unsigned int dimensions, class TValue, typename std::enable_if<std::is_arithmetic<TValue>::value>::type * = nullptr>
	void operator*=(VectorBase<T, dimensions>& vector, const TValue value)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			vector[i] *= value;
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
	template<class T, unsigned int dimensions>
	bool operator==(const VectorBase<T, dimensions>& a, const VectorBase<T, dimensions>& b)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			if (a[i] != b[i])
				return false;
		}

		return true;
	}
	template<class T, unsigned int dimensions>
	bool operator!=(VectorBase<T, dimensions>& a, VectorBase<T, dimensions>& b)
	{
		return !(a == b);
	}
}