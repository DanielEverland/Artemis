#pragma once

#include<memory>
#include<Renderer.h>

using std::unique_ptr;

class Window
{
public:
	Window();
	~Window();

	void Show();
	void Draw() const;
	
private:
	bool IsShown;
	struct SDL_Window* WindowPtr;
	unique_ptr<Renderer> RendererPtr;
};