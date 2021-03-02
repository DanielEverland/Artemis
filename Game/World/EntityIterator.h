#pragma once

#include <map>
#include <memory>

#include <Game/World/Entity.h>

using std::shared_ptr;
using std::map;

typedef map<void*, shared_ptr<Entity>> EntityMap;
typedef EntityMap::iterator Iterator;

template<class T>
class EntityIterator
{
public:
	explicit EntityIterator(EntityMap& map);

	T* operator->() const;
	operator bool() const;
	EntityIterator& operator++();
	
	void Reset();
	
private:
	Iterator CurrentIterator;
	Iterator BeginIterator;
	Iterator EndIterator;
};


template <class T>
EntityIterator<T>::EntityIterator(EntityMap& map)
{
	CurrentIterator = map.begin();
	BeginIterator = map.begin();
	EndIterator = map.end();
}

template <class T>
T* EntityIterator<T>::operator->() const
{
	return dynamic_cast<T*>(CurrentIterator->second.get());
}

template <class T>
EntityIterator<T>::operator bool() const
{
	return CurrentIterator != EndIterator;
}

template <class T>
EntityIterator<T>& EntityIterator<T>::operator++()
{
	do
	{
		++CurrentIterator;
	}
	while (!dynamic_cast<T*>(CurrentIterator->second.get()) && CurrentIterator != EndIterator);
	
	return *this;
}

template <class T>
void EntityIterator<T>::Reset()
{
	CurrentIterator = BeginIterator;
}

