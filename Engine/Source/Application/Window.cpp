#include "Window.h"

#include <iostream>
#include <SDL_events.h>


#include "Rendering/Renderer.h"

using namespace ArtemisEngine;

#define SHAPE_SIZE 64

DefineLogCategory(LogWindow, Verbosity::VeryVerbose)

Window::Window()
{
    MainWindow = SDL_CreateWindow("Artemis", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GetWidth(), GetHeight(), 0);

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(MainWindow, &wmInfo);
    Handle = wmInfo.info.win.window;

	
    MainRenderer = new Renderer(this);
	
    /* The loading of the background texture. Since SDL_LoadBMP() returns
    a surface, we convert it to a texture afterwards for fast accelerated
    blitting. */
    //Loading_Surf = SDL_LoadBMP("C:\\Users\\Daniel\\Desktop\\Background.bmp");
    //Background_Tx = SDL_CreateTextureFromSurface(Renderer, Loading_Surf);
    //SDL_FreeSurface(Loading_Surf); /* we got the texture now -> free surface */

    ///* Load an additional texture */
    //Loading_Surf = SDL_LoadBMP("C:\\Users\\Daniel\\Desktop\\Blueshapes.bmp");
    //BlueShapes = SDL_CreateTextureFromSurface(Renderer, Loading_Surf);
    //SDL_FreeSurface(Loading_Surf);
}

Window::~Window()
{
    /* The renderer works pretty much like a big canvas:
    when you RenderCopy() you are adding paint, each time adding it
    on top.
    You can change how it blends with the stuff that
    the new data goes over.
    When your 'picture' is complete, you show it
    by using SDL_RenderPresent(). */

    /* SDL 1.2 hint: If you're stuck on the whole renderer idea coming
    from 1.2 surfaces and blitting, think of the renderer as your
    main surface, and SDL_RenderCopy() as the blit function to that main
    surface, with SDL_RenderPresent() as the old SDL_Flip() function.*/

    /*SDL_DestroyTexture(BlueShapes);
    SDL_DestroyTexture(Background_Tx);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(MainWindow);*/
}

void Window::Update()
{
	int* x = new int;
	int* y = new int;
	SDL_PumpEvents();
	SDL_GetMouseState(x, y);

    /*(*x) = static_cast<int>((GetWidth() / 2.f) - (*x));
    (*y) = static_cast<int>((GetHeight() / 2.f) - (*y));*/

	float relX = static_cast<float>(*x) / GetWidth();
	float relY = static_cast<float>(*y) / GetHeight();

	float rotX = relX * 360.f;
	float rotY = relY * 360.f;
	
    Log(LogWindow, Verbosity::Log,
		format("x: {}, y: {}", to_string(rotX), to_string(rotY)));

	MainRenderer->GetMainCamera()->SetRotation(rotX, rotY, 0.f);
	
	delete x;
	delete y;
}

void Window::Draw()
{
	MainRenderer->DoRender();
}

SDL_Window* Window::GetRaw()
{
	return MainWindow;
}

HWND Window::GetHandle()
{
	return Handle;
}

Renderer* Window::GetRenderer()
{
	return MainRenderer;
}

int32 Window::GetWidth()
{
	return 1920;
}

int32 Window::GetHeight()
{
    return 1080;
}