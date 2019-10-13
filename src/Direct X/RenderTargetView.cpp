#include "RenderTargetView.h"
#include "DirectXHelper.h"

RenderTargetView::RenderTargetView(const shared_ptr<const SwapChain> swapChain, const shared_ptr<const GraphicsDevice> graphicsDevice) : GraphicsResource(graphicsDevice)
{
	ThrowIfFailed(swapChain->GetRawSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));
	ThrowIfFailed(graphicsDevice->GetRawDevice()->CreateRenderTargetView(backBuffer.Get(), 0, &renderTargetView));
}

ComPtr<ID3D11RenderTargetView> RenderTargetView::GetRawRenderTargetView() const
{
	return renderTargetView;
}

void RenderTargetView::Clear(const float* clearColor) const
{
	GetGraphicsDevice()->GetRawContext()->ClearRenderTargetView(renderTargetView.Get(), clearColor);
}