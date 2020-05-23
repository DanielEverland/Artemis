#pragma once

#include "Private/Game/Object Management/IObject.h"
#include "Private/Game/Object Management/GlobalObjectManager.h"

namespace ArtemisEngine
{
	class Object : public IObject
	{
	public:
		Object() : uniqueID(GlobalObjectManager::CreateUniqueID())
		{
			GlobalObjectManager::RegisterID(GetUniqueID());
		}
		~Object()
		{
			GlobalObjectManager::RemoveID(GetUniqueID());
		}

		[[nodiscard]] unsigned int GetUniqueID() const override;
		[[nodiscard]] virtual bool IsInstantiated() const override;

		virtual void Begin() override;

	protected:
		static class World* GetWorld();

		virtual void SetInstantiated(bool value) override;
		
	private:
		const unsigned int uniqueID;
		bool instantiated;
	};
}