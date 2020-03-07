#pragma once
#include <memory>

namespace ArtemisEngine::Rendering
{
	using std::unique_ptr;

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
		
		const int BufferSize;
		const unique_ptr<T[]> Elements;

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

	private:
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