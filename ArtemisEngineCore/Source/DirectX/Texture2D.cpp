#include "Texture2D.h"
#include "DirectXHelper.h"

Texture2D::Texture2D(UINT width, UINT height, const shared_ptr<const GraphicsDevice> graphicsDevice)
{
	this->graphicsDevice = graphicsDevice;
	this->width = width;
	this->height = height;
	this->mipmapLevel = 1;

	CreateTextureResource();
}
Texture2D::Texture2D(UINT width, UINT height, UINT mipmap, const shared_ptr<const GraphicsDevice> graphicsDevice)
{
	this->graphicsDevice = graphicsDevice;
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

void Texture2D::Resize(UINT width, UINT height)
{
	this->width = width;
	this->height = height;

	CreateTextureResource();
}

void Texture2D::CreateTextureResource(D3D11_TEXTURE2D_DESC description)
{
	ThrowIfFailed(graphicsDevice->GetRawDevice().Get()->CreateTexture2D(&description, 0, &textureResource));
}

D3D11_TEXTURE2D_DESC Texture2D::GetDescription()
{
	D3D11_TEXTURE2D_DESC description;
	
	description.Width = this->width;
	description.Height = this->height;
	description.MipLevels = this->mipmapLevel;
	description.MiscFlags = DefaultMiscFlags;
	description.BindFlags = DefaultBindFlags;
	description.CPUAccessFlags = DefaultCPUAccessFlag;
	description.ArraySize = 1;
	description.Format = DefaultFormat;
	description.Usage = DefaultUsage;
	
	graphicsDevice->GetMSAASupport(description.Format, &description.SampleDesc.Count, &description.SampleDesc.Quality);

	return description;
}