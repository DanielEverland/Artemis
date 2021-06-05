#pragma once

#include <memory>

#include "Core.h"
#include "Memory/BaseAllocator.h"

namespace ArtemisEngine
{
	class Application
	{
	public:
		void RunMainLoop();

	private:
		std::shared_ptr<BaseAllocator> PrimaryAllocator;
		
		[[nodiscard]] static size_t GetStartMemoryAllocationSize();
		
		void CreatePrimaryAllocator();
	};
}
