// Invisible Walls is the sole owner of all rights of, and to the video game First Class Trouble and affiliated projects and retains all rights to concepts and ideas from First Class Trouble, which are not transferred herein, and retains all common law copyrights and trademarks to the given title.
#include "Renderer.h"
#include <Color.h>
#include "RendererCore.h"

Renderer::Renderer(SDL_Window* sdlWindow) : BackgroundColor(Color::Black), RendererPtr(SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer)
{
}

Renderer::Renderer(SDL_Window* sdlWindow, Color backgroundColor) : BackgroundColor(backgroundColor), RendererPtr(SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer)
{
}

void Renderer::Clear() const
{
	SetDrawColor(BackgroundColor);
	THROW_IF_FAILED(SDL_RenderClear(GetRawRenderer()));
}

void Renderer::Present() const
{
	SDL_RenderPresent(GetRawRenderer());
}

void Renderer::SetDrawColor(Color drawColor) const
{
	THROW_IF_FAILED(SDL_SetRenderDrawColor(GetRawRenderer(), drawColor.R, drawColor.G, drawColor.B, drawColor.A));
}

void Renderer::FillRect(const SDL_Rect& rect) const
{
	THROW_IF_FAILED(SDL_RenderFillRect(GetRawRenderer(), &rect));
}

SDL_Renderer* Renderer::GetRawRenderer() const
{
	return RendererPtr.get();
}
