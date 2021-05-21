#include "pch.h"


#include "Exception/ArgumentException.h"
#include "Exception/OutOfMemoryException.h"
#include "Exception/Exception.h"

using namespace ArtemisEngine;

TEST(ExceptionTests, BaseExceptionStringConstructor)
{
	const auto message = string("Message");
	const auto exception = Exception(message);
	EXPECT_EQ(exception.what(), message);
}

TEST(ExceptionTests, BaseExceptionCBasedStringConstructor)
{
	const auto exception = Exception("Message");
	EXPECT_EQ(exception.what(), static_cast<string>("Message"));
}

TEST(ExceptionTests, ArgumentExceptionStringConstructor)
{
	const auto message = string("Message");
	const auto exception = ArgumentException(message);
	EXPECT_EQ(exception.what(), message);
}

TEST(ExceptionTests, ArgumentExceptionCBasedStringConstructor)
{
	const auto exception = ArgumentException("Message");
	EXPECT_EQ(exception.what(), static_cast<string>("Message"));
}

TEST(ExceptionTests, OutOfMemoryExceptionStringConstructor)
{
	const auto message = string("Message");
	const auto exception = OutOfMemoryException(message);
	EXPECT_EQ(exception.what(), message);
}

TEST(ExceptionTests, OutOfMemoryExceptionCBasedStringConstructor)
{
	const auto exception = OutOfMemoryException("Message");
	EXPECT_EQ(exception.what(), static_cast<string>("Message"));
}