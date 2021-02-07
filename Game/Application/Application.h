#pragma once

#include "Window/Window.h"

class Application
{
public:
	Application();
	~Application();
	
	bool Initialize();
	void Start();

private:
	unique_ptr<Window> WindowPtr;

	bool InitializeCore();
	
	bool InitializeSDL();
	void ExecuteMainLoop();
	bool MainLoop() const;
};
