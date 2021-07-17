#include "Application.h"

//#define SDL_MAIN_HANDLED
//#include "SDL.h"

#include "Core/SizeDef.h"
#include "Memory/FreeListAllocator.h"
#include "Core.h"
#include <SDL_events.h>
#include <SDL.h>

using namespace ArtemisEngine;

DefineLogCategory(LogApplication, Verbosity::VeryVerbose)

Application::Application()
{
	Log(LogApplication, Verbosity::Verbose, FuncName)
	
    InitializeSDL();
    CreatePrimaryAllocator();
    CreateMainWindow();
}

Application::~Application()
{
    Log(LogApplication, Verbosity::Verbose, FuncName)
	
	MainWindow.reset();
}

void Application::RunMainLoop()
{
    Log(LogApplication, Verbosity::Verbose, FuncName)
	
    while (true)
    {
        if (!MainLoop())
            break;
    }

    SDL_Quit();
}

void Application::CreatePrimaryAllocator()
{
    Log(LogApplication, Verbosity::Verbose, FuncName)
	
	const size_t size = GetStartMemoryAllocationSize();
	void* ptr = malloc(size);
    PrimaryAllocator = std::make_shared<FreeListAllocator>(ptr, size);
}

void Application::CreateMainWindow()
{
    Log(LogApplication, Verbosity::Verbose, FuncName)
	
    MainWindow = std::make_unique<Window>();
}

size_t Application::GetStartMemoryAllocationSize()
{
    Log(LogApplication, Verbosity::Verbose, FuncName)
	
	return megabyte * 250;
}

bool Application::MainLoop() const
{	
    SDL_Event ev;

    while (SDL_PollEvent(&ev) != 0)
    {
        Log(LogApplication, Verbosity::VeryVerbose, "SDL Event: " + std::to_string(ev.type))
    	
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

void Application::InitializeSDL()
{
    Log(LogApplication, Verbosity::Verbose, FuncName)
	
    if (SDL_Init(0) < 0) {
        system("pause");
    }
}
