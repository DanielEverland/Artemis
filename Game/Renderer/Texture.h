#pragma once

#include <string>
#include <memory>
#include <Renderer/RendererCore.h>

class Texture
{
public:
	Texture(const std::string& filePath);

	SDL_Texture* GetRawTexture() const;

private:
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> RawTexture;
};
