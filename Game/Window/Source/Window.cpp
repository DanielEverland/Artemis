#include<Renderer.h>

#include "Window.h"
#include "WindowCore.h"

Window::Window() : IsShown(false), WindowPtr(nullptr), RendererPtr(nullptr)
{
}

Window::~Window()
{
	if(IsShown)
	{
		// Destroy the window. This will also destroy the surface
		SDL_DestroyWindow(WindowPtr);
	}
}

void Window::Show()
{
	// Create our window
	WindowPtr = SDL_CreateWindow("Artemis", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

	// Make sure creating the window succeeded
	if (!WindowPtr) {
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		system("pause");
		return;
	}

	RendererPtr = std::make_unique<Renderer>(WindowPtr);

	IsShown = true;
}

void Window::Draw() const
{
	RendererPtr->Clear();

	RendererPtr->SetDrawColor(Color::White);
	RendererPtr->FillRect({ 10, 10, 10, 10 });
	
	RendererPtr->Present();
}
