#include <Game/Game.h>

#include <Game/Renderer/RendererCore.h>
#include "Application.h"
#include "Core/Config/GameConfiguration.h"
#include "../Modding/ModLoader.h"
#include <Core/Debugging/Verbosity.h>
#include <Core/Debugging/Logger.h>

#include "Game/World/Character.h"

Application* Application::Instance = nullptr;

namespace
{
	const string LogCategoryApplication = "Application";
}

Application* Application::Get()
{
	return Instance;
}

Application::Application()
{
	Instance = this;
	StartTime = clock();
}

Application::~Application()
{
	SDL_Quit();
}

void Application::Start() const
{
	ExecuteMainLoop();
}

void Application::LoadLevel()
{
	CurrentWorld = std::make_unique<World>();
}

float Application::GetTime() const
{
	return (clock() - StartTime) / (float)CLOCKS_PER_SEC;
}

bool Application::InitializeCore()
{
	bool initializationFailed = false;

	Exception::InitializeSymbols();
	initializationFailed |= !InitializeSDL();
	GameConfiguration::Load();
	
	return !initializationFailed;
}

bool Application::Initialize()
{
	bool initializationFailed = false;

	initializationFailed |= !InitializeCore();

	LoadLevel();
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

void Application::ExecuteMainLoop() const
{
	CallLuaApplicationStarted();

	while (true)
	{
		TRY_START
		
		if (!MainLoop())
			break;

		TRY_END(LogCategoryApplication, Verbosity::Error)
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

	CurrentWorld->Tick();
	WindowPtr->Draw();

	return true;
}

void Application::CallLuaApplicationStarted() const
{
	for(auto iter = ModLoader::GetAllLuaFiles().begin(); iter != ModLoader::GetAllLuaFiles().end(); ++iter)
	{
		LuaState* luaState = (*iter).second.get();
		if(luaState->HasFunction(JsonApplicationStartFunctionName))
		{
			luaState->CallFunction(JsonApplicationStartFunctionName);
		}
	}

	Character::Create(GetWorld());
}
