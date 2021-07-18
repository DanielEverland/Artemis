#include "Window.h"
#include <iostream>

using namespace ArtemisEngine;

#define SHAPE_SIZE 64

Window::Window()
{
    MainWindow = SDL_CreateWindow("Artemis", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 580, 0);
    MainRenderer = std::make_unique<Renderer>(MainWindow);
	
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
    std::cout << "test" << std::endl;
    /* Rectangles for drawing which will specify source (inside the texture)
   and target (on the screen) for rendering our textures. */
    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = SHAPE_SIZE;
    SrcR.h = SHAPE_SIZE;

    DestR.x = 640 / 2 - SHAPE_SIZE / 2;
    DestR.y = 580 / 2 - SHAPE_SIZE / 2;
    DestR.w = SHAPE_SIZE;
    DestR.h = SHAPE_SIZE;

    /* render background, whereas NULL for source and destination
            rectangles just means "use the default" */
    //SDL_RenderCopy(Renderer, Background_Tx, NULL, NULL);

    ///* render the current animation step of our shape */
    //SDL_RenderCopy(Renderer, BlueShapes, &SrcR, &DestR);
    //SDL_RenderPresent(Renderer);
}
