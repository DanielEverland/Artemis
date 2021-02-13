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

private:
	static Application* Instance;
	
	unique_ptr<Window> WindowPtr;
	unique_ptr<World> CurrentWorld;

	bool InitializeCore();
	
	bool InitializeSDL();
	void ExecuteMainLoop() const;
	bool MainLoop() const;
	static void CallLuaApplicationStarted();
};
