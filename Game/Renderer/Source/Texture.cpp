#include "Texture.h"

#include "RendererCore.h"

Texture::Texture(const std::string& filePath) : RawTexture(nullptr, SDL_DestroyTexture)
{
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());

	if(!surface)
		throw SDLException("Couldn't load " + filePath);
	
	RawTexture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(SDL_CreateTextureFromSurface(Renderer::GetPrimaryRenderer()->GetRawRenderer(), surface), SDL_DestroyTexture);

	if(!RawTexture)
		throw SDLException("Couldn't convert surface to texture for file " + filePath);
	
	SDL_FreeSurface(surface);
}

SDL_Texture* Texture::GetRawTexture() const
{
	return RawTexture.get();
}
