#pragma once

#include"RendererCore.h"
#include<memory>

#include<Color.h>

class Renderer
{
public:	
	explicit Renderer(SDL_Window* sdlWindow);
	explicit Renderer(SDL_Window* sdlWindow, Color backgroundColor);

	static Renderer* GetPrimaryRenderer();
	static void SetPrimaryRenderer(Renderer* renderer);
	
	void FillRect(const SDL_Rect& rect) const;
	void DrawTexture(SDL_Texture* texture, const SDL_Rect& rect) const;
	
	void Clear() const;
	void Present() const;
	void SetDrawColor(Color drawColor) const;
	SDL_Renderer* GetRawRenderer() const;
		
private:
	static Renderer* PrimaryRenderer;
	
	Color BackgroundColor;
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> RendererPtr;
};
