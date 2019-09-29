#include "Texture2D.h"
#include "GraphicsResource.h"

Texture2D::Texture2D(UINT width, UINT height, shared_ptr<GraphicsDevice> graphicsDevice) : GraphicsResource(graphicsDevice)
{
	this->width = width;
	this->height = height;
	this->mipmapLevel = 1;

	CreateTextureResource();
}
Texture2D::Texture2D(UINT width, UINT height, UINT mipmap, shared_ptr<GraphicsDevice> graphicsDevice) : GraphicsResource(graphicsDevice)
{
	this->width = width;
	this->height = height;
	this->mipmapLevel = mipmap;

	CreateTextureResource();
}

void Texture2D::CreateTextureResource()
{
	D3D11_TEXTURE2D_DESC description = GetDescription();

	CreateTextureResource(description);
}

void Texture2D::CreateTextureResource(D3D11_TEXTURE2D_DESC description)
{
	shared_ptr<GraphicsDevice> graphicsDevice = GetGraphicsDevice();

	ThrowIfFailed(graphicsDevice->GetRawDevice().Get()->CreateTexture2D(&description, 0, &textureResource));
}

D3D11_TEXTURE2D_DESC Texture2D::GetDescription()
{
	D3D11_TEXTURE2D_DESC description;
	shared_ptr<GraphicsDevice> graphicsDevice = GetGraphicsDevice();

	description.Width = this->width;
	description.Height = this->height;
	description.MipLevels = this->mipmapLevel;
	description.MiscFlags = 0;

	if (graphicsDevice->SupportsMSAA())
	{
		description.SampleDesc.Count = graphicsDevice->GetMSAASampleCount();
		description.SampleDesc.Quality = graphicsDevice->GetMSAAQuality();
	}
	else
	{
		description.SampleDesc.Count = 1;
		description.SampleDesc.Quality = 0;
	}

	return description;
}