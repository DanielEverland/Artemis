#pragma once

#include "../World/World.h"
#include "../Window/Window.h"

class Application
{
public:
	static Application* Get();
	
	Application();
	~Application();

	[[nodiscard]] World* GetWorld() const { return CurrentWorld.get(); }

	bool Initialize();
	void Start() const;
	void LoadLevel();
	float GetTime() const;

private:
	static Application* Instance;

	clock_t StartTime;
	unique_ptr<Window> WindowPtr;
	unique_ptr<World> CurrentWorld;

	bool InitializeCore();
	
	bool InitializeSDL();
	void ExecuteMainLoop() const;
	bool MainLoop() const;
	void CallLuaApplicationStarted() const;
};
