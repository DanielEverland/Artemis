#pragma once

#include <list>

#include "Private/Game/Object Management/IUpdateObject.h"
#include "Private/Game/Object Management/SafeObjRef.h"

#include "Private/Game/Object Management/IObject.h"

using std::list;

namespace ArtemisWindow
{
	class GameWindow;
}

namespace ArtemisEngine
{
	class World
	{
		friend ArtemisWindow::GameWindow;
		
	public:
		[[nodiscard]] static SafePtr<World> GetWorld();

		template<class T>
		static SafePtr<T> Instantiate();
		template<class T>
		static SafePtr<T> Instantiate(T*&& obj);

	private:
		static SafeObjRef<World> worldInstance;
		static list<SafeObjRef<IObject>> instantiatedObjects;
		static list<SafePtr<IUpdateObject>> updateObjects;

		static void UpdateState();
		static void InstantiateObject(SafePtr<IObject> obj);
		static void AddToUpdateList(const SafePtr<IUpdateObject>& updateObj);
	};

	template<class T>
	SafePtr<T> World::Instantiate()
	{
		return Instantiate(new T());
	}

	template<class T>
	SafePtr<T> World::Instantiate(T*&& obj)
	{
		static_assert(std::is_base_of<IObject, T>::value, "Cannot create object that does not derive from IObject");
		
		instantiatedObjects.push_back(SafeObjRef<IObject>(std::move(obj)));
		SafePtr<T> createdObject = instantiatedObjects.end()->GetSafePtr<T>();

		InstantiateObject(createdObject);
		
		return createdObject;
	}
}
