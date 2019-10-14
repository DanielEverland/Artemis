#include "DepthBuffer.h"
#include "DirectXHelper.h"

DepthBuffer::DepthBuffer(UINT width, UINT height, const shared_ptr<const GraphicsDevice> graphicsDevice) : Texture2D(width, height, 1, graphicsDevice)
{
	CreateTextureResource();
	CreateStencilView();
}

void DepthBuffer::CreateStencilView()
{
	const shared_ptr<const GraphicsDevice> graphicsDevice = GetGraphicsDevice();

	ThrowIfFailed(graphicsDevice->GetRawDevice()->CreateDepthStencilView(textureResource.Get(), 0, &stencilView));
}

void DepthBuffer::Resize(UINT width, UINT height)
{
	Texture2D::Resize(width, height);

	CreateStencilView();
}

D3D11_TEXTURE2D_DESC DepthBuffer::GetDescription()
{
	D3D11_TEXTURE2D_DESC description = Texture2D::GetDescription();

	description.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	description.Usage = D3D11_USAGE_DEFAULT;
	description.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	GetGraphicsDevice()->GetMSAASupport(description.Format, &description.SampleDesc.Count, &description.SampleDesc.Quality);

	return description;
}

ComPtr<ID3D11DepthStencilView> DepthBuffer::GetRawStencilView() const
{
	return stencilView;
}

void DepthBuffer::Clear() const
{
	GetGraphicsDevice()->GetRawContext()->ClearDepthStencilView(stencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}