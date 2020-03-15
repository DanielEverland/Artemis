#include "DepthBuffer.h"
#include "DirectXHelper.h"

DepthBuffer::DepthBuffer(const IWindow* window, const shared_ptr<const GraphicsDevice> graphicsDevice)
	: Texture2D(window->GetWidth(), window->GetHeight(), 1, graphicsDevice)
{
	this->window = window;

	CreateTextureResource();
	CreateStencilView();
}

void DepthBuffer::CreateStencilView()
{
	ThrowIfFailed(graphicsDevice->GetRawDevice()->CreateDepthStencilView(textureResource.Get(), 0, &stencilView));
}

void DepthBuffer::Resize()
{
	Texture2D::Resize(window->GetWidth(), window->GetHeight());

	CreateStencilView();
}

D3D11_TEXTURE2D_DESC DepthBuffer::GetDescription()
{
	D3D11_TEXTURE2D_DESC description = Texture2D::GetDescription();

	description.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	description.Usage = D3D11_USAGE_DEFAULT;
	description.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	graphicsDevice->GetMSAASupport(description.Format, &description.SampleDesc.Count, &description.SampleDesc.Quality);

	return description;
}

ComPtr<ID3D11DepthStencilView> DepthBuffer::GetRawStencilView() const
{
	return stencilView;
}

void DepthBuffer::Clear() const
{
	graphicsDevice->GetRawContext()->ClearDepthStencilView(stencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}