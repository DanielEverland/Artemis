#include <iostream>
#include <Renderer/RendererCore.h>
#include <Window/Window.h>
#include <memory>
#include <Exception.h>
#include <Debugging/GameplayDebugger.h>


#include "GameConfiguration.h"
#include "Modding/ModLoader.h"

void ExecuteMainLoop();
void LoadCoreEssentials();
void LoadCore();
bool Initialize();
bool MainLoop();
void Kill();

using std::unique_ptr;

unique_ptr<Window> WindowPtr;

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args)
{
	if(!Initialize())
		return -1;

	LoadCoreEssentials();
	LoadCore();
	ExecuteMainLoop();
	
	return 0;
}

void LoadCoreEssentials()
{
	GameConfiguration::Load();
}

void LoadCore()
{
	ModLoader::LoadMods();
}

void ExecuteMainLoop()
{
	while (true)
	{
		try
		{
			if (!MainLoop())
				break;
		}
		catch (const Exception& e)
		{
			std::cout << "Caught exception in main loop\n" << e.GetMessageW() << std::endl;
		}
		catch (const std::exception&)
		{
			std::cout << "Caught std exception in main loop" << std::endl;
		}
	}
}

bool Initialize()
{
	// Initialize SDL. SDL_Init will return -1 if it fails.
	if (SDL_Init(0) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	WindowPtr = std::make_unique<Window>();
	if(!WindowPtr)
		return false;
	
	WindowPtr->Show();
	return true;
}

bool MainLoop()
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

	WindowPtr->Draw();
	
	return true;
}

void Kill()
{
	SDL_Quit();
}