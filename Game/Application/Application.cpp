﻿#include <Game.h>

#include <Renderer/RendererCore.h>
#include "Application.h"

#include "Config/GameConfiguration.h"
#include "Modding/ModLoader.h"

Application::Application()
{
}

Application::~Application()
{
	SDL_Quit();
}

void Application::Start()
{
	ExecuteMainLoop();
}

bool Application::InitializeCore()
{
	bool initializationFailed = false;
	
	initializationFailed |= !InitializeSDL();
	GameConfiguration::Load();
	
	return !initializationFailed;
}

bool Application::Initialize()
{
	bool initializationFailed = false;

	initializationFailed |= !InitializeCore();
	
	ModLoader::LoadMods();

	return !initializationFailed;
}

bool Application::InitializeSDL()
{
	// Initialize SDL. SDL_Init will return -1 if it fails.
	if (SDL_Init(0) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	WindowPtr = std::make_unique<Window>();
	if (!WindowPtr)
		return false;

	WindowPtr->Show();
	return true;
}

void Application::ExecuteMainLoop()
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

	WindowPtr->Draw();

	return true;
}
