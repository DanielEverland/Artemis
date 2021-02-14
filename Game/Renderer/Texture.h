#pragma once

#include <string>
#include <memory>

#include <Game/Renderer/RendererCore.h>

class Texture
{
public:
	Texture(const std::string& filePath);

	SDL_Texture* GetRawTexture() const;

	[[nodiscard]] int GetWidth() const;
	[[nodiscard]] int GetHeight() const;

private:
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> RawTexture;
	int Width;
	int Height;
};
