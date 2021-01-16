#pragma once

#include"RendererCore.h"
#include<memory>

#include<Color.h>

class Renderer
{
public:
	explicit Renderer(SDL_Window* sdlWindow);
	explicit Renderer(SDL_Window* sdlWindow, Color backgroundColor);

	void Clear() const;
	void Present() const;
	void SetDrawColor(Color drawColor) const;
	void FillRect(const SDL_Rect& rect) const;
	SDL_Renderer* GetRawRenderer() const;
	
private:
	Color BackgroundColor;
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> RendererPtr;
};
