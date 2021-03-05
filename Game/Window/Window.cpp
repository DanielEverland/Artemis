#include "Window.h"
#include "WindowCore.h"
#include <Game/Framework/Application.h>
#include <Game/World/EntityIterator.h>
#include <Game/World/Entity.h>

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
	Renderer::SetPrimaryRenderer(RendererPtr.get());

	IsShown = true;
}

void Window::Draw() const
{
	RendererPtr->Clear();

	//Texture texture("Resources/Smiley.bmp");
	//RendererPtr->DrawTexture(texture.GetRawTexture(), { 10, 10, 300, 300} );

	//RendererPtr->SetDrawColor(Color::White);
	//RendererPtr->FillRect({ 10, 10, 10, 10 });
	
	for(auto iter = GetWorld()->GetEntityIterator<Entity>(); iter; ++iter)
	{
#pragma warning(push, 0)
		auto test = iter->Scripts;
		if(test.size() > 0)
			bool hasFunction = iter->Scripts[0]->HasFunction("Draw");
	}
	
	RendererPtr->Present();
}

World* Window::GetWorld()
{
	return Application::GetWorld();
}
