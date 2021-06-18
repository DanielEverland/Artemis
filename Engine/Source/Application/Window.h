#pragma once

#define SDL_MAIN_HANDLED
#include <SDL_render.h>
#include <SDL_video.h>

#include "Core.h"

namespace ArtemisEngine
{
	class Window
	{
	public:
		Window();
		~Window();
		void Draw();
		
	private:
		SDL_Window* MainWindow;
		SDL_Renderer* Renderer;

		// TEMP SHIT:
		SDL_Surface* Loading_Surf;
		SDL_Texture* Background_Tx;
		SDL_Texture* BlueShapes;
	};
}
