#include "pch.h"

#include "Engine/ComponentContainer.h"
#include <chrono>
#include <memory>
#include <thread>

//TEST(ComponentContainerTest, EmptyContainer)
//{
//	ComponentContainer container;
//
//
//	ExpectEqual(0, container.GetCount());
//}
//TEST(ComponentContainerTest, AddComponent)
//{
//	ComponentContainer container;
//
//
//	IComponent* testComponent = container.AddComponent<IComponent>();
//
//
//	ExpectEqual(1, container.GetCount());
//	ExpectTrue(testComponent != nullptr);
//}
//TEST(ComponentContainerTest, Contains)
//{
//	ComponentContainer container;
//
//
//	IComponent* testComponent = container.AddComponent<IComponent>();
//
//
//	ExpectTrue(container.Contains(testComponent));
//}
//TEST(ComponentContainerTest, RemoveComponent)
//{
//	ComponentContainer container;
//
//
//	IComponent* testComponent = container.AddComponent<IComponent>();
//	container.RemoveComponent(testComponent);
//
//
//	ExpectFalse(container.Contains(testComponent));
//}

class TestClassB
{
public:
	int testValue = 5;
};

class TestClass
{
public:
	TestClassB*&& get()
	{
		obj = new TestClassB();
		return std::move(obj);
	}
	void Delete()
	{
		delete obj;
		obj = nullptr;
	}

private:
	TestClassB* obj;
	TestClassB** ptr;
};

TEST(ComponentContainerTest, ComponentDeallocation)
{
	TestClass* test = new TestClass();
	TestClassB* ptr = std::move(test->get());

	test->Delete();

	int wat = ptr->testValue;

	if (!ptr)
	{
		bool yay = true;
	}
	else
	{
		bool noo = true;
	}
}