#pragma once
#include <memory>

#include "Exceptions/NullReferenceException.h"
#include "Exceptions/OutOfRangeException.h"

namespace ArtemisEngine::Rendering
{
	using std::shared_ptr;

	template<class T>
	struct RenderingBufferDataContainer
	{
	public:
		RenderingBufferDataContainer() : BufferSize(0)
		{
		}
		RenderingBufferDataContainer(int size) : BufferSize(size), Elements(new T[size])
		{
		}
		
		shared_ptr<T[]> Elements;

		int GetBufferSize() const
		{
			return BufferSize;
		}
		T& operator[](int index)
		{
			ThrowIfInvalidIndex(index);

			return Elements[index];
		}
		T operator[](int index) const
		{
			ThrowIfInvalidIndex(index);

			return Elements[index];
		}
		void operator=(RenderingBufferDataContainer& other)
		{
			BufferSize = other.BufferSize;
			Elements.swap(other.Elements);
		}
		void operator=(RenderingBufferDataContainer&& other)
		{
			BufferSize = other.BufferSize;
			Elements.swap(other.Elements);

			other.BufferSize = 0;
			other.Elements = 0;
		}

	private:
		int BufferSize;

		void ThrowIfInvalidIndex(int index) const
		{
			if (Elements.get() == nullptr)
				throw NullReferenceException("Attempted to index unitialized rendering buffer");
			else if (index < 0)
				throw OutOfRangeException("Rendering buffer indexer < 0");
			else if (index >= BufferSize)
				throw OutOfRangeException("Rendering buffer indexer >= BufferSize");
		}
	};
}