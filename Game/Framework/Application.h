#pragma once

#include "Window/Window.h"

class Application
{
public:
	Application();
	~Application();
	
	bool Initialize();
	void Start() const;

private:
	unique_ptr<Window> WindowPtr;

	bool InitializeCore();
	
	bool InitializeSDL();
	void ExecuteMainLoop() const;
	bool MainLoop() const;
	static void CallLuaApplicationStarted();
};
