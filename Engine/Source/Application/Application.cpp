#include "Application.h"

//#define SDL_MAIN_HANDLED
//#include "SDL.h"

#include "Core/SizeDef.h"
#include "Memory/FreeListAllocator.h"
#include "Core.h"

using namespace ArtemisEngine;

DefineLogCategory(LogApplication, Verbosity::VeryVerbose)

Application::Application()
{
	Log(LogApplication, Verbosity::Verbose, __FUNCTION__)
	
    InitializeSDL();
    CreatePrimaryAllocator();
    CreateMainWindow();
}

Application::~Application()
{
    Log(LogApplication, Verbosity::Verbose, __FUNCTION__)
	
	MainWindow.reset();
	
    //SDL_Quit();
}

void Application::RunMainLoop()
{
    Log(LogApplication, Verbosity::Verbose, __FUNCTION__)
	
    while (true)
    {
        if (!MainLoop())
            break;
    }
}

void Application::CreatePrimaryAllocator()
{
    Log(LogApplication, Verbosity::Verbose, __FUNCTION__)
	
	const size_t size = GetStartMemoryAllocationSize();
	void* ptr = malloc(size);
    PrimaryAllocator = std::make_shared<FreeListAllocator>(ptr, size);
}

void Application::CreateMainWindow()
{
    Log(LogApplication, Verbosity::Verbose, __FUNCTION__)
	
    MainWindow = std::make_unique<Window>();
}

size_t Application::GetStartMemoryAllocationSize()
{
    Log(LogApplication, Verbosity::Verbose, __FUNCTION__)
	
	return megabyte * 250;
}

bool Application::MainLoop() const
{	
    /*SDL_Event ev;

    while (SDL_PollEvent(&ev) != 0)
    {
        switch (ev.type)
        {
        case SDL_QUIT:
            return false;
        default:
            break;
        }
    }*/

	MainWindow->Draw();

	return true;
}

void Application::InitializeSDL()
{
    Log(LogApplication, Verbosity::Verbose, __FUNCTION__)
	
    // Initialize SDL. SDL_Init will return -1 if it fails.
    /*if (SDL_Init(0) < 0) {
        system("pause");
    }*/
}
