#include "RenderTargetView.h"

RenderTargetView::RenderTargetView(const shared_ptr<const SwapChain> swapChain, const shared_ptr<const GraphicsDevice> graphicsDevice)
{
	swapChain->GetRawSwapChain().Get()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.Get()));
	graphicsDevice->GetRawDevice()->CreateRenderTargetView(backBuffer.Get(), 0, &renderTargetView);
}

ComPtr<ID3D11RenderTargetView> RenderTargetView::GetRawRenderTargetView() const
{
	return renderTargetView;
}