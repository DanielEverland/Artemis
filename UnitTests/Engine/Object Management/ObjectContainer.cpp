#include "pch.h"

#include "Source/Game/Object Management/ObjectContainer.h"
#include "Include/Game/SafePtr.h"

using namespace ArtemisEngine;

class TestClass
{
};

class Base
{
public:
	virtual void Test() { }
};

class A : public Base
{
};

class B : public Base
{
};

class AA : public A
{

};

TEST(ObjectContainerTest, AddObject)
{
	ObjectContainer<Base> container;


	SafePtr<Base> basePtr = container.Add<Base>();
	SafePtr<A> aPtr = container.Add<A>();
	SafePtr<AA> aaPtr = container.Add<AA>();


	ExpectTrue(basePtr.IsValid());
	ExpectTrue(aPtr.IsValid());
	ExpectTrue(aaPtr.IsValid());
}
TEST(ObjectContainerTest, RemoveObject)
{
	ObjectContainer<TestClass> container;
	SafePtr<TestClass> ptr = container.Add<TestClass>();


	container.Remove(ptr);


	ExpectTrue(ptr.IsValid() == false);
}
TEST(ObjectContainerTest, RemoveObjectRaw)
{
	ObjectContainer<TestClass> container;
	SafePtr<TestClass> ptr = container.Add<TestClass>();
	TestClass* rawPtr = ptr;


	container.Remove(rawPtr);


	ExpectTrue(ptr.IsValid() == false);
}
TEST(ObjectContainerTest, Contains)
{
	ObjectContainer<TestClass> container;
	SafePtr<TestClass> ptr = container.Add<TestClass>();
	SafePtr<TestClass> emptyPtr = {};

	SafePtr<TestClass> removedPtr = container.Add<TestClass>();
	container.Remove(removedPtr);



	ExpectTrue(container.Contains(ptr));
	ExpectTrue(container.Contains(removedPtr) == false);
	ExpectTrue(container.Contains(emptyPtr) == false);
}
TEST(ObjectContainerTest, ContainsRaw)
{
	ObjectContainer<TestClass> container;
	TestClass* ptr = container.Add<TestClass>();
	TestClass* emptyPtr = nullptr;

	TestClass* removedPtr = container.Add<TestClass>();
	container.Remove(removedPtr);



	ExpectTrue(container.Contains(ptr));
	ExpectTrue(container.Contains(emptyPtr) == false);
	ExpectTrue(container.Contains(removedPtr) == false);
	ExpectTrue(container.Contains<TestClass>(nullptr) == false);
}
TEST(ObjectContainerTest, Destruction)
{
	ObjectContainer<TestClass>* container = new ObjectContainer<TestClass>();
	SafePtr<TestClass> ptr = container->Add<TestClass>();


	delete container;


	ExpectTrue(ptr.IsValid() == false);
}
TEST(ObjectContainerTest, Get)
{
	ObjectContainer<Base> container;
	container.Add<A>();

	SafePtr<A> a = container.Get<A>();
	SafePtr<B> b = container.Get<B>();

	ExpectTrue(a.IsValid() == true);
	ExpectTrue(b.IsValid() == false);
}