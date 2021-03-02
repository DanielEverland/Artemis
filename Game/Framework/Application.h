#pragma once

#include "../World/World.h"
#include "../Window/Window.h"

class Application
{
public:
	static Application* Get();
	
	Application();
	~Application();

	[[nodiscard]] static World* GetWorld() { return Instance->CurrentWorld.get(); }
	[[nodiscard]] static shared_ptr<LuaState> GetGlobalLuaState() { return Instance->GlobalLuaState; }
	
	bool Initialize();
	void Start() const;
	void LoadLevel();
	float GetTime() const;

private:
	static Application* Instance;

	clock_t StartTime;
	unique_ptr<Window> WindowPtr;
	unique_ptr<World> CurrentWorld;
	shared_ptr<LuaState> GlobalLuaState;

	bool InitializeCore();
	
	bool InitializeSDL();
	void ExecuteMainLoop() const;
	bool MainLoop() const;
	void CallLuaApplicationStarted() const;
};
