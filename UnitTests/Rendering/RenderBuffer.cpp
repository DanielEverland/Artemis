#include "pch.h"

#include "Engine/Rendering/RenderingBuffer.h"
#include "Exceptions/NullReferenceException.h"
#include "Exceptions/OutOfRangeException.h"

namespace Rendering::Buffer
{
	using namespace ArtemisEngine::Rendering;

	typedef RenderingBuffer<int> Buffer;

	TEST(Buffer, EmptyConstructor)
	{
		Buffer buff;


		ExpectEqual(0, buff.BufferSize);
		ExpectEqual(nullptr, buff.Elements.get());
	}
	TEST(Buffer, EmptyConstructorIndexingException)
	{
		Buffer buff;


		ExpectThrow(buff[0], NullReferenceException);
	}
	TEST(Buffer, ConstEmptyConstructorIndexingException)
	{
		const Buffer buff;


		ExpectThrow(buff[0], NullReferenceException);
	}
	TEST(Buffer, Indexing)
	{
		Buffer buff(3);


		buff[0] = 3;
		

		ExpectEqual(3, buff[0]);
	}
	TEST(Buffer, ConstIndexing)
	{
		const Buffer buff(3);


		// We can't be sure what the values are initialized to,
		// so we don't check for equality
		int value = buff[0];
	}
	TEST(Buffer, OutOfRangeIndexingException)
	{
		Buffer buff(3);

		
		ExpectThrow(buff[-1], OutOfRangeException);
		ExpectThrow(buff[3], OutOfRangeException);
	}
	TEST(Buffer, ConstOutOfRangeIndexingException)
	{
		const Buffer buff(3);


		ExpectThrow(buff[-1], OutOfRangeException);
		ExpectThrow(buff[3], OutOfRangeException);
	}
}