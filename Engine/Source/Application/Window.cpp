#include "Window.h"

#include <iostream>

#include "Rendering/Renderer.h"

using namespace ArtemisEngine;

#define SHAPE_SIZE 64

Window::Window()
{
    MainWindow = SDL_CreateWindow("Artemis", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GetWidth(), GetHeight(), 0);
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

void Window::Draw()
{
	MainRenderer->DoRender();
}

SDL_Window* Window::GetRaw()
{
	return MainWindow;
}

int32 Window::GetHeight()
{
	return 640;
}

int32 Window::GetWidth()
{
	return 580;
}
