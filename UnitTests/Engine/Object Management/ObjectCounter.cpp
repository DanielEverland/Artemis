#include "pch.h"

#include "Private/Game/Object Management/ObjectCounter.h"
#include "Public/Game/SafePtr.h"

using namespace ArtemisEngine;

class TestClass
{
};

TEST(ObjectCounterTest, Construction)
{
	ObjectCounter* counter = new ObjectCounter(new TestClass);

	ExpectTrue(counter->IsAlive());
}
TEST(ObjectCounterTest, ConstructionNullPtr)
{
	ExpectThrow(new ObjectCounter(nullptr), NullReferenceException);
}
TEST(ObjectCounterTest, GettingSafePtr)
{
	ObjectCounter* counter = new ObjectCounter(new TestClass());

	SafePtr<TestClass> ptr = counter->GetSafePtr<TestClass>();

	ExpectTrue(ptr.IsValid());
}
TEST(ObjectCounterTest, Deleting)
{
	ObjectCounter* counter = new ObjectCounter(new TestClass());

	SafePtr<TestClass> ptr = counter->GetSafePtr<TestClass>();
	counter->Delete();

	ExpectFalse(ptr.IsValid());
}
TEST(ObjectCounterTest, DeletingTwice)
{
	ObjectCounter* counter = new ObjectCounter(new TestClass());

	// This is necessary to prevent the object counter from deleting itself
	SafePtr ptr = counter->GetSafePtr<TestClass>();

	// Just making sure this doesn't throw any exceptions
	counter->Delete();
	counter->Delete();
}
TEST(ObjectCounterTest, DeleteSelf)
{
	ObjectCounter* counter = new ObjectCounter(new TestClass());

	{
		SafePtr<TestClass> ptr = counter->GetSafePtr<TestClass>();
	}

	counter->Delete();

	// Can't check this, just making sure the function is valid and being called.
}
TEST(ObjectCounterTest, GetRaw)
{
	ObjectCounter* counter = new ObjectCounter(new TestClass());

	ExpectTrue(counter->GetRaw<TestClass>() != nullptr);
}