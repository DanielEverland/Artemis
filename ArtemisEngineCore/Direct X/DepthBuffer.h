#pragma once

#include "Texture2D.h"
#include "Windows/IWindow.h"

using namespace ArtemisWindow;

class DepthBuffer : protected Texture2D
{
public:
	explicit DepthBuffer(const IWindow* window, const shared_ptr<const GraphicsDevice> graphicsDevice);

	ComPtr<ID3D11DepthStencilView> GetRawStencilView() const;
	void Clear() const;
	void Resize();

protected:
	D3D11_TEXTURE2D_DESC GetDescription() override;

private:
	void CreateStencilView();

	ComPtr<ID3D11DepthStencilView> stencilView;

	const IWindow* window;
};