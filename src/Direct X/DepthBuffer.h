#pragma once

#include "Texture2D.h"

class DepthBuffer : protected Texture2D
{
public:
	explicit DepthBuffer(UINT width, UINT height, shared_ptr<GraphicsDevice> graphicsDevice);

protected:
	virtual D3D11_TEXTURE2D_DESC GetDescription();

private:
	void CreateStencilView();

	ComPtr<ID3D11DepthStencilView> stencilView;
};