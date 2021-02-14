#include "Texture.h"

#include "RendererCore.h"

Texture::Texture(const std::string& filePath) : RawTexture(nullptr, SDL_DestroyTexture)
{
	SDL_Surface* surface = IMG_Load(filePath.c_str());

	if(!surface)
		throw SDLException("Couldn't load " + filePath + " due to error: " + SDL_GetError());

	Width = surface->w;
	Height = surface->h;
	
	RawTexture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(SDL_CreateTextureFromSurface(Renderer::GetPrimaryRenderer()->GetRawRenderer(), surface), SDL_DestroyTexture);

	string err = SDL_GetError();
	if(!RawTexture)
		throw SDLException("Couldn't convert surface to texture for file " + filePath + " due to error: " + SDL_GetError());
	
	SDL_FreeSurface(surface);
}

SDL_Texture* Texture::GetRawTexture() const
{
	return RawTexture.get();
}

int Texture::GetHeight() const
{
	return Height;
}

int Texture::GetWidth() const
{
	return Width;
}
