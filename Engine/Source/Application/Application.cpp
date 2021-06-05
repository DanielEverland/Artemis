#include "Application.h"
#include "SDL.h"
#include "Core/SizeDef.h"
#include "Memory/FreeListAllocator.h"

using namespace ArtemisEngine;

Application::~Application()
{
	MainWindow.reset();
	
    SDL_Quit();
}

void Application::RunMainLoop()
{
	CreatePrimaryAllocator();
    CreateMainWindow();

    while (true)
    {
        if (!MainLoop())
            break;
    }
}

void Application::CreatePrimaryAllocator()
{
	const size_t size = GetStartMemoryAllocationSize();
	void* ptr = malloc(size);
    PrimaryAllocator = std::make_shared<FreeListAllocator>(ptr, size);
}

void Application::CreateMainWindow()
{
    MainWindow = std::make_unique<Window>();
}

size_t Application::GetStartMemoryAllocationSize()
{
	return megabyte * 250;
}

bool Application::MainLoop() const
{
    SDL_Event ev;

    while (SDL_PollEvent(&ev) != 0)
    {
        switch (ev.type)
        {
        case SDL_QUIT:
            return false;
        default:
            break;
        }
    }

	MainWindow->Draw();

	return true;
}
