#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wrl.h>
#include <memory>
#include <d3d11.h>

#include "DirectXHelper.h"
#include "GraphicsResource.h"

using Microsoft::WRL::ComPtr;
using std::shared_ptr;

class Texture2D : protected GraphicsResource
{
public:
	explicit Texture2D(UINT width, UINT height, const shared_ptr<const GraphicsDevice> graphicsDevice);
	explicit Texture2D(UINT width, UINT height, UINT mipmap, const shared_ptr<const GraphicsDevice> graphicsDevice);

protected:	
	virtual D3D11_TEXTURE2D_DESC GetDescription();

	void CreateTextureResource();
	void CreateTextureResource(D3D11_TEXTURE2D_DESC description);

	ComPtr<ID3D11Texture2D> textureResource;

private:
	UINT width;
	UINT height;
	UINT mipmapLevel;	
};