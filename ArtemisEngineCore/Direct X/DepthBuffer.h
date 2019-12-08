#pragma once

#include "Texture2D.h"

class DepthBuffer : protected Texture2D
{
public:
	explicit DepthBuffer(UINT width, UINT height, const shared_ptr<const GraphicsDevice> graphicsDevice);

	ComPtr<ID3D11DepthStencilView> GetRawStencilView() const;
	void Clear() const;
	void Resize(UINT width, UINT height);

protected:
	D3D11_TEXTURE2D_DESC GetDescription() override;

private:
	void CreateStencilView();

	ComPtr<ID3D11DepthStencilView> stencilView;
};