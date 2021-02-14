#include "pch.h"

#include <memory>

using std::unique_ptr;
using std::weak_ptr;

class TestClass
{
public:
	void TestFunc() { }
	int Value;
};

TEST(World, ExpiredPointer)
{
	const int ExpectedValue = 5;
	weak_ptr<TestClass> obj;
	
	{
		auto smartPtr = std::make_shared<TestClass>();
		obj = smartPtr;
		smartPtr->Value = ExpectedValue;
		EXPECT_FALSE(obj.expired());
	}

	EXPECT_TRUE(obj.expired());
}