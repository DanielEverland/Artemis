#pragma once

#define SDL_MAIN_HANDLED
#include <SDL_render.h>
#include <SDL_video.h>

#include "Core.h"

namespace ArtemisEngine
{
	class Renderer;
	
	class Window
	{
	public:
		Window();
		~Window();
		
		void Draw();

		[[nodiscard]] SDL_Window* GetRaw();
		[[nodiscard]] int32 GetWidth();
		[[nodiscard]] int32 GetHeight();
		
	private:
		SDL_Window* MainWindow;
		Renderer* MainRenderer;

		// TEMP SHIT:
		SDL_Surface* Loading_Surf;
		SDL_Texture* Background_Tx;
		SDL_Texture* BlueShapes;
	};
}
