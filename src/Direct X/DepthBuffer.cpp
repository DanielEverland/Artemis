#include "DepthBuffer.h"

DepthBuffer::DepthBuffer(UINT width, UINT height, const shared_ptr<const GraphicsDevice> graphicsDevice) : Texture2D(width, height, 1, graphicsDevice)
{
	CreateStencilView();
}

void DepthBuffer::CreateStencilView()
{
	const shared_ptr<const GraphicsDevice> graphicsDevice = GetGraphicsDevice();

	ThrowIfFailed(graphicsDevice->GetRawDevice()->CreateDepthStencilView(textureResource.Get(), 0, &stencilView));
}

D3D11_TEXTURE2D_DESC DepthBuffer::GetDescription()
{
	D3D11_TEXTURE2D_DESC description = Texture2D::GetDescription();

	description.ArraySize = 1;
	description.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	description.Usage = D3D11_USAGE_DEFAULT;
	description.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	description.CPUAccessFlags = 0;
}

ComPtr<ID3D11DepthStencilView> DepthBuffer::GetRawStencilView() const
{
	return stencilView;
}