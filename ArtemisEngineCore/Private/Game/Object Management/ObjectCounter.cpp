#include "ObjectCounter.h"
#include "Include/Exceptions/NullReferenceException.h"

#include <utility>

using namespace ArtemisEngine;

ObjectCounter::ObjectCounter(void*&& obj)
{
	if (obj == nullptr)
		throw NullReferenceException("Attempted to create object counter for nullptr");

	this->isAlive = true;
	this->obj = std::move(obj);
	this->watchers = 0;
}

void ObjectCounter::Delete()
{
	if (!isAlive)
		return;

	isAlive = false;

	if (obj != nullptr)
		delete obj;
	
	obj = nullptr;

	DeleteSelfIfReady();
}

bool ObjectCounter::IsAlive() const
{
	return isAlive;
}

void ObjectCounter::RemoveWatcher()
{
	watchers--;

	DeleteSelfIfReady();
}

void ObjectCounter::AddWatcher()
{
	watchers++;
}

void ObjectCounter::DeleteSelfIfReady()
{
	if (watchers <= 0 && isAlive == false)
		delete this;
}
