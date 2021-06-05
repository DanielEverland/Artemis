#pragma once

#include <memory>

#include "Window.h"
#include "Memory/BaseAllocator.h"

namespace ArtemisEngine
{
	class Application
	{
	public:
		Application();
		~Application();
		
		void RunMainLoop();

	private:
		std::shared_ptr<BaseAllocator> PrimaryAllocator;
		std::unique_ptr<Window> MainWindow;		
		
		[[nodiscard]] static size_t GetStartMemoryAllocationSize();

		bool MainLoop() const;
		static void InitializeSDL();
		void CreatePrimaryAllocator();
		void CreateMainWindow();
	};
}
